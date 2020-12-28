//
//  DSSCallViewModule.m
//  Pods
//
//  Created by 28404 on 2017/11/6.
//

#import "DSSCallViewModule.h"
#import <DHMediaPlay/DHMediaPlay-swift.h>
#import <AVFoundation/AVFoundation.h>
#import <LCOpenSDKDynamic/LCOpenSDK_LoginManager.h>
#import <DHSipSDK/HttpAPI.h>
#import <DHSipSDK/HttpAPI+Extend.h>
#import <DHSipSDK/SipManager.h>
#import "DHDataCenter.h"

#import <sys/socket.h>
#import <sys/sysctl.h>
#import <net/if.h>
#import <net/if_dl.h>
#import <mach/mach.h>
#import <arpa/inet.h>
#import <ifaddrs.h>

#define IOS_CELLULAR    @"pdp_ip0"
#define IOS_WIFI        @"en0"
//#define IOS_VPN       @"utun0"
#define IP_ADDR_IPv4    @"ipv4"
#define IP_ADDR_IPv6    @"ipv6"

static NSTimeInterval maxRingTime = 30;     ///< 最大响铃时长
static NSTimeInterval maxCallTime = 2*60;   ///< 最大通话时长

@interface DSSCallViewModule ()

@property (nonatomic, strong) DSSCallInfo *callInfo;
@property (nonatomic, assign) BOOL isOpenedDoor;            ///< 是否已开门
@property (nonatomic, strong) RtpOUdpTalkCamera *rtpSipTalkCamera;     ///< camera
@property (nonatomic, strong) Camera *rtspPlayCamera;

@property (nonatomic, strong) NSTimer *ringTimer;           ///< 响铃timer
@property (nonatomic, strong) NSTimer *callTimer;           ///< 呼叫timer
@property (nonatomic, strong) NSTimer *vibrateTimer;        ///< 震动timer
@property (nonatomic, assign) NSInteger ringTimeInterval;   ///< 呼叫倒计时
@property (nonatomic, assign) NSInteger callTimeInterval;   ///< 通话时长
@property (nonatomic, strong) NSDate *contactTime;  // 存储通话记录用。呼入时间，如果接通，改为接通时间

@end

@implementation DSSCallViewModule

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (instancetype)init
{
    if (self = [super init]) {
        _dismissSubject = [RACSubject subject];
        _startRingSubject = [RACSubject subject];
        _stopRingSubject = [RACSubject subject];
        _startVibrateSubject = [RACSubject subject];
        _stopVibrateSubject = [RACSubject subject];
        _playVideoSubject = [RACSubject subject];
        _stopVideoSubject = [RACSubject subject];
        _startTalkSubject = [RACSubject subject];
        _stopTalkSubject = [RACSubject subject];
        _openDoorSubject = [RACSubject subject];
        
        _ringTimeInterval = maxRingTime;
        _callTimeInterval = 0;
        
        _stopButtonHidden = YES;
        _authButtonHidden = YES;
        _openDoorButtonHidden = YES;
        _loadingVideoLabelHidden = YES;
        _playWindowHidden = NO;  // 视频窗口默认需要展示 否则会当做异常
        _canPlayVideo = YES;
        _isMuteHidden = YES;
        _isHandsFreeHidden = YES;
        _isHandsFreeOn = YES;
        _exchangeButtonHidden = NO;
        _exchangedCallStyle = CallStyleAudioVideo;
        self.incomingLabelText = @"00:30";
        BOOL handsFreeEnable = ![self isHeadsetPluggedIn];
        if (handsFreeEnable != self.handsFreeEnable) {
            self.handsFreeEnable = handsFreeEnable;
        }
        
        [self registerNotification];
    }
    return self;
}

- (void)registerNotification {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillEnterForeground:) name:UIApplicationWillEnterForegroundNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidEnterBackground:) name:UIApplicationDidEnterBackgroundNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(audioRouteChangeListenerCallback:)   name:AVAudioSessionRouteChangeNotification object:nil];//设置通知
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillTerminateNotification:)   name:UIApplicationWillTerminateNotification object:nil];//设置通知
}

- (void)applicationWillEnterForeground:(NSNotification *)notification {
    // 恢复视频播放
    [self resumePlayVideo];
    [self.startRingSubject sendNext:nil];
}

- (void)applicationDidEnterBackground:(NSNotification *)notification
{
    // 停止视频播放
    [_stopVideoSubject sendNext:nil];
    self.rtspPlayCamera = nil;
}

- (void)setInviteParam:(DSSInviteVTParam *)inviteParam
{
    _inviteParam = inviteParam;
    
    self.contactTime = [NSDate date];
    // 组装camera
    [self initTalkCamera:inviteParam];
    [self queryChannelInfo:inviteParam resume:YES callback:NULL];
}

- (void)initTalkCamera:(DSSInviteVTParam *)inviteParam {
    self.rtpSipTalkCamera = [[RtpOUdpTalkCamera alloc] init];
    self.rtpSipTalkCamera.callType = inviteParam.callType;
    self.rtpSipTalkCamera.serverIp = inviteParam.rtpServerIP;
    self.rtpSipTalkCamera.port = inviteParam.rtpAudioPort;              ///< 音频端口
    self.rtpSipTalkCamera.vPort = inviteParam.rtpVideoPort;              ///< 视频端口
    self.rtpSipTalkCamera.userId = inviteParam.userID;
    self.rtpSipTalkCamera.callId = inviteParam.callID;
    self.rtpSipTalkCamera.dlgId = inviteParam.dialogID;
    self.rtpSipTalkCamera.tId = inviteParam.tID;
    self.rtpSipTalkCamera.sampleDepth = inviteParam.audioBits;                    ///< 采样深度
    self.rtpSipTalkCamera.sampleRate = inviteParam.sampleRate;                  ///< 采样深度
    self.rtpSipTalkCamera.localIp = [self getIPAddress:true];
    self.rtpSipTalkCamera.isCall = NO;
}


static dispatch_queue_t CallModuleGetP2PQueue()
{
    // We want all instances to share the same queue since they will be reading/writing the same files.
    static dispatch_queue_t queue;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        queue = dispatch_queue_create("com.facebook.RCTNativeBusiness.p2pQueue", DISPATCH_QUEUE_SERIAL);
    });
    return queue;
}

- (void)initPlayCameraChannelId:(DSSChannelInfo *)channelInfo {
    [_stopVideoSubject sendNext:nil];
    __block typeof(self) weakself = self;
    dispatch_async(CallModuleGetP2PQueue(), ^{
        NSLog(@"=============查询视频URL 1111");
        
        // 如果处在前台模式 才能直接播放 （因为在后台 直接触发play会render失败）
        dispatch_async(dispatch_get_main_queue(), ^{
            if (channelInfo) {
                Camera* camera = [self getCameraFromChannelInfo:channelInfo];
                weakself.rtspPlayCamera = camera;
                weakself.canPlayVideo = YES;
                weakself.exchangeButtonHidden = NO;
                if (MBL_UNIT_PERIMETER == channelInfo.chnlUnitType) {
                    weakself.authButtonHidden = NO;
                    weakself.openDoorButtonHidden = YES;
                } else {
                    weakself.authButtonHidden = YES;
                    weakself.openDoorButtonHidden = NO;
                }
                weakself.playWindowHidden = (self.exchangedCallStyle == CallStyleAudio);
                weakself.loadingVideoLabelHidden = (self.exchangedCallStyle == CallStyleAudio);
                if ([UIApplication sharedApplication].applicationState != UIApplicationStateBackground) {
                    NSLog(@"=============查询视频URL 2222 前台直接播放");
                    [weakself.playVideoSubject sendNext:weakself.rtspPlayCamera];
                } else {
                    NSLog(@"=============查询视频URL 2222 后台不能播放 清除camera");
                    // 如果查询到rtspURL的时候 处于后台不能播放， 由于rtsp地址有个token有效期， 而如果延迟到切回前台播放的话可能会播放失败，因此索性之前删除camera，切回前台重新查询
                    weakself.rtspPlayCamera = nil;
                }
            } else { // APP 呼叫不显示
                weakself.rtspPlayCamera = nil;
            }
            
            
            
        });
    });
}

- (Camera*) getCameraFromChannelInfo:(DSSChannelInfo*)info {
//    RCTUserModule *user = [UserExtraProvider sharedInstance].user;
    if ([info.accessSource integerValue] == 0) {
        // 上级
        LCRTCamera *rtCamera        = [[LCRTCamera alloc] init];
        rtCamera.accessTok          = [DHDataCenter shareInstance].lcToken;//user.lcToken;
        rtCamera.psk                = info.deviceId;
        rtCamera.deviceID           = info.deviceId;
        rtCamera.channelNo          = info.channelid ? [info.channelid integerValue] : 0;
        rtCamera.streamType         = 1;
        return rtCamera;
    } else { // [info.accessSource integerValue] = 1
        // 下级
        NSUInteger port = [self p2pPort];
        NSString* host = [DHDataCenter shareInstance].serviceHost;
        NSURL* url = [NSURL URLWithString:host];
        NSInteger serverPort = url.port ? [url.port integerValue] : 80;
        NSString* serverIP = url.host ?: @"";
        NSString* dpRestToken = [[NSString alloc] initWithFormat:@"Bearer %@", [DHDataCenter shareInstance].token];
        NSTimeInterval timeZoneOffset = [[NSTimeZone systemTimeZone] secondsFromGMT];

        CommunityCloudRTCamera* communityCamera = [[CommunityCloudRTCamera alloc] init];
        communityCamera.dpRestToken  = dpRestToken;
        communityCamera.serverIP     = serverIP;
        communityCamera.serverPort   = serverPort;
        communityCamera.channelId    = info.channelid;
        communityCamera.streamType   = 2;
        communityCamera.communityCode= [DHDataCenter shareInstance].communityCode;
        communityCamera.isP2P        = port != 0;
        communityCamera.clientId     = [[DHDataCenter shareInstance].userId intValue];
        communityCamera.clientType   = 1;
        communityCamera.deviceType   = info.chnlUnitType;
        communityCamera.version      = @"v12";
        communityCamera.timeoffset   = timeZoneOffset * 1000; // 毫秒
        communityCamera.isUseHttps   = [host.uppercaseString containsString:@"HTTPS"] ? 1 : 0;
        communityCamera.userAgent    = @"Client/2.0 HSWX";
        communityCamera.connType     = 0;
        return communityCamera;
    }
}

// p2p打洞
- (NSUInteger)p2pPort {
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:@{ @"Sn": self.inviteParam.fromAdr?:@"", @"Type": @(1), @"Port": @(9100), @"User": @"", @"Pwd": @"" } options:NSJSONWritingPrettyPrinted error:&error];
    
    NSString *jsonString;
    
    if (!jsonData) {
        
        NSLog(@"%@",error);
        
    }else{
        
        jsonString = [[NSString alloc]initWithData:jsonData encoding:NSUTF8StringEncoding];
        
    }
    NSLog(@"=============P2P打洞11111");
    NSUInteger port = jsonString ? [[LCOpenSDK_LoginManager shareMyInstance] getP2PPort:jsonString timeout:10000] : 0;
    if (port != 0) {
        NSLog(@"=============P2P打洞22222成功");
    } else {
        NSLog(@"=============P2P打洞22222失败");
    }
    return port;
}

- (NSString *) p2pUrlByUrl:(NSString *)rtspUrl port:(NSUInteger)port{
    NSString *respURL = rtspUrl;
    if (port != 0) {
        NSString *subStr = [respURL substringFromIndex:7];
        NSArray *array = [subStr componentsSeparatedByString:@"/"];
        if (array.count) {
            NSString *firStr = array.firstObject;
            NSString *route = [subStr substringFromIndex:firStr.length];
            respURL = [NSString stringWithFormat:@"rtsp://127.0.0.1:%lu%@",(unsigned long)port,route];
        }
    }
    return respURL;
}
#pragma mark - Interface

- (BOOL)isAPPCall {
    return self.inviteParam && self.inviteParam.isAPP;
}

- (void)resumePlayVideo {
    if (!_playVideoSubject) {
        return;
    }
    // 当前没网或者APP处于非活动状态 都不处理播放
    if (![_delegate isNetConnected] || [UIApplication sharedApplication].applicationState == UIApplicationStateBackground) {
        return;
    }
    // 如果有通道信息 则查询播放地址播放，否则先查询通道信息
    if (self.doorChannel) {
        [self initPlayCameraChannelId:self.doorChannel];
    } else {
        [self queryChannelInfo:_inviteParam resume:NO callback:NULL];
    }
}

- (void)queryChannelInfo:(DSSInviteVTParam *)inviteParam resume:(BOOL)resume callback:(void (^)())callback{
    if ([self isAPPCall]) {
        self.deviceNameLabelText = inviteParam.userID?:@"";
        [self initPlayCameraChannelId:nil];
        return;
    }
    __block typeof(self) blockself = self;
    NSMutableDictionary* dicParam = [[NSMutableDictionary alloc] initWithDictionary:@{@"callNum":inviteParam.userID?:@"", @"deviceId":inviteParam.deviceID?:@""}];
    if (inviteParam.fromAdr) {
        [dicParam setValue:inviteParam.fromAdr forKey:@"communityCode"];
    }
    NSLog(@"🍎-->%@", dicParam);
    [[HttpAPI shareInstance] queryChannelInfo:dicParam success:^(DSSChannelInfo * channelInfo) {
        if (channelInfo) {
            blockself.doorChannel = channelInfo;
            blockself.deviceNameLabelText = channelInfo.name?:(inviteParam.userID?:@"");
            NSLog(@"=============查询通道信息 222222");
            [blockself initPlayCameraChannelId:channelInfo];
            if (callback) {
                callback();
            }
        } else {
            if (resume) {
                [blockself queryChannelInfo:inviteParam resume:NO callback:callback];
            } else {
                NSLog(@"Failed to get video channel information.");
                blockself.deviceNameLabelText = inviteParam.userID?:@"";
                if (callback) {
                    callback();
                }
            }
        }
    } fail:^(NSError * error) {
        NSLog(@"获取设备详情失败%@",error);
        if (resume) {
            [blockself queryChannelInfo:inviteParam resume:NO callback:callback];
        } else {
            NSLog(@"Failed to get video channel information.");
            blockself.deviceNameLabelText = inviteParam.userID?:@"";
            if (callback) {
                callback();
            }
        }
    }];
}

- (void)handleViewDidLoad
{
    // 响铃
    if ([UIApplication sharedApplication].applicationState != UIApplicationStateBackground) {
        [self.startRingSubject sendNext:nil];
    }
    self.vibrateTimer = [NSTimer scheduledTimerWithTimeInterval:2.0 target:self selector:@selector(checkVibrateTime:) userInfo:nil repeats:YES];
    // 呼叫倒计时
    self.ringTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(checkRingTime:) userInfo:nil repeats:YES];
}

#pragma mark Action

// 拒绝
- (void)handleRefuseCall
{
    NSLog(@"handleRefuseCall %@ %s", [self class], __FUNCTION__);
    
    [[SipManager shareInstance] RejectDisturbWithKey:self.inviteParam.key withCid:self.inviteParam.cid];
    [self doCommonOperationAfterStopCall];
}

// 接听
- (void)handleAgreeCall
{
    NSLog(@"handleAgreeCall %@ %s", [self class], __FUNCTION__);
    [self.ringTimer invalidate];
    self.ringTimer = nil;
    [self.vibrateTimer invalidate];
    self.vibrateTimer = nil;
    [self stopRingAndVibrate];
    self.isAgreed = YES;
    self.contactTime = [NSDate date];
    self.refuseButtonHidden = YES;
    self.agreeButtonHidden = YES;
    self.stopButtonHidden = NO;
    self.incomingLabelText = @"02:00";
    self.isMuteHidden = NO;
    self.isHandsFreeHidden = NO;
    self.callTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(checkCallTime:) userInfo:nil repeats:YES];
    // 1.收到SC通知
    // 2.开始对讲
    // 3.收到播放组件库按顺序回调的ASession, APort, Vsession, VPort后，InviteVTCall
    [self.startTalkSubject sendNext:self.rtpSipTalkCamera];
}

- (void)handleSessionIdAndPortArrived
{
    [[SipManager shareInstance] AcceptCallingWithKey:self.inviteParam.key withCid:self.inviteParam.cid];
}

// 开门
- (void)handleOpenDoor
{
    if (!self.doorChannel.channelid) {
        __weak typeof(self) weakSelf = self;
        [self queryChannelInfo:self.inviteParam resume:NO callback:^{
            if (weakSelf.doorChannel.channelid) {
             [weakSelf _handleOpenDoor];
            } else {
                [weakSelf.openDoorSubject sendError:nil];
            }
        }];
    } else {
        [self _handleOpenDoor];
    }
}

- (void)_handleOpenDoor {
    __block typeof(self) blockself = self;
//    RCTUserModule *user = [UserExtraProvider sharedInstance].user;
    NSNumber *accessSource = self.doorChannel.accessSource?:@(0);
    NSString *communityCode = self.inviteParam.fromAdr?:@"";
    NSString *deviceId = [accessSource integerValue] == 1 ? [NSString stringWithFormat:@"%@-%@", communityCode, self.doorChannel.basicParentid]?:@"" : self.doorChannel.basicParentid;
    NSMutableDictionary *disParam = [[NSMutableDictionary alloc] initWithDictionary: @{@"deviceId"      : deviceId?:@"",
                                                                                       @"channelId"     : self.doorChannel.unitSeq?:@(0),
                                                                                       @"accessSource"  : accessSource,
                                                                                       @"type"          : @"remote",
                                                                                       @"communityCode" : communityCode,
                                                                                       @"companyId"     : [DHDataCenter shareInstance].companyID?:@""}];
    if ([DHDataCenter shareInstance].personFileID) {
        [disParam setValue:[DHDataCenter shareInstance].personFileID forKey:@"personFileId"];
        [disParam setValue:@(1) forKey:@"userType"];
    }
    [[HttpAPI shareInstance] openDoor:disParam success:^{
        blockself.isOpenedDoor = true;
        [blockself.openDoorSubject sendCompleted];
    } fail:^(NSError * _error) {
        [blockself.openDoorSubject sendError:nil];
    }];
}

- (void)handleCancelCall
{
    NSLog(@"handleCancelCall %@ %s", [self class], __FUNCTION__);
    [[SipManager shareInstance] HangUpCallingWithKey:self.inviteParam.key withCid:self.inviteParam.cid];
    
    [self doCommonOperationAfterStopCall];
}

// 授权
- (void)authSuccess:(void (^)(void))successBack fail:(void (^)(NSError*))failBack
{
//    RCTUserModule *user = [UserExtraProvider sharedInstance].user;
    NSString *communityCode = self.inviteParam.fromAdr?:@"";
    NSString *deviceCode = self.doorChannel.basicParentid?:@"";
    
    [[HttpAPI shareInstance] auth: @{@"params": @{
                                             @"deviceCode": deviceCode,
                                             @"authType": @(3),
                                             @"anthResult": @(0),
                                             @"phone": [DHDataCenter shareInstance].phoneNumber ? : @""},
                                     @"method": @"mas.visitor.authFlag",
                                     @"communityCode": communityCode
    }success:^{
        if (successBack) {
            successBack();
        }
    } fail:^(NSError * error) {
        if (failBack) {
            failBack(error);
        }
    }];
}

// 处理切换播放模式（音频 Or 音频+视频）
- (void)handleExchangeCall
{
    if (!self.isAgreed) {
        self.playWindowHidden = YES;
        self.loadingVideoLabelHidden = YES;
        [self handleAgreeCall];
        self.exchangedCallStyle = CallStyleAudio;
    } else {
        if (self.exchangedCallStyle == CallStyleAudio) {
            if (self.canPlayVideo) {
                self.exchangedCallStyle = CallStyleAudioVideo;
                self.playWindowHidden = NO;
                if (![_delegate isPlaying]) {
                    [self resumePlayVideo];
                }
            }
        } else {
            self.loadingVideoLabelHidden = YES;
            self.exchangedCallStyle = CallStyleAudio;
            self.playWindowHidden = YES;
        }
    }
}

// 处理静音
- (void)handleMute
{
    self.isMuteOn = !self.isMuteOn;
}

// 处理免提
- (void)handleHandsFree
{
    self.isHandsFreeOn = !self.isHandsFreeOn;
}


#pragma mark Notification
- (void)handleFirstFrameArrive
{
    self.playWindowHidden = (self.exchangedCallStyle == CallStyleAudio);
    self.loadingVideoLabelHidden = YES;
}

- (void)handleAudioSessionIdCallBack:(NSString *)sessionId
{
    self.inviteParam.audioSessionID = [sessionId integerValue];
}

- (void)handleAudioPortCallBack:(NSString *)port
{
    self.inviteParam.rtpAudioPort = [port integerValue];
}

- (void)handleVideoSessionIdCallBack:(NSString *)sessionId
{
    self.inviteParam.videoSessionID = [sessionId integerValue];
}

- (void)handleVideoPortCallBack:(NSString *)port
{
    self.inviteParam.rtpVideoPort = [port integerValue];
    [self handleSessionIdAndPortArrived];
}

- (void)handleCancelCallNofity:(NSNotification *)notify
{
    NSLog(@"handleCancelCallNofity %@ %s", [self class], __FUNCTION__);
    [self doCommonOperationAfterStopCall];
}

- (void)handleByeCallNofity:(NSNotification *)notify
{
    NSLog(@"handleByeCallNofity %@ %s", [self class], __FUNCTION__);
    // 可视对讲呼叫被挂断，释放链接
    
    [self doCommonOperationAfterStopCall];
}

#pragma mark - Private
- (void)checkRingTime:(NSTimer *)timer
{
    self.ringTimeInterval --;
    self.incomingLabelText = [NSString stringWithFormat:@"00:%02ld", (long)self.ringTimeInterval];
    if (self.ringTimeInterval <= 0) {
        [self handleRefuseCall];
    }
}

- (void)checkCallTime:(NSTimer *)timer
{
    self.callTimeInterval ++;
    if (self.callTimeInterval >= maxCallTime) {
        [self handleCancelCall];
    } else {
        //设置计时时间
        int countDown = maxCallTime - self.callTimeInterval;
        NSInteger min = countDown / 60;
        NSInteger sec = countDown % 60;
        NSString *strTime = [NSString stringWithFormat:@"%02ld:%02ld", (long)min, (long)sec];
        self.incomingLabelText = strTime;
    }
}

- (void)checkVibrateTime:(NSTimer *)timer
{
    dispatch_async(dispatch_get_main_queue(), ^{
        //震动
        if ([UIApplication sharedApplication].applicationState != UIApplicationStateBackground){
            [self.startVibrateSubject sendNext:nil];
        }
    });
}

// 在对讲停止后执行的通用操作
- (void)doCommonOperationAfterStopCall
{
    dispatch_async(dispatch_get_main_queue(), ^{

        [self stopRingAndVibrate];
        
        // 0.如果使用系统的呼叫界面，report结束使用

        
        // 1.如果响铃计时器不为空，销毁并置空
        if (self.ringTimer) {
            NSLog(@"invalidate ringTimer %@ %s", [self class], __FUNCTION__);
            [self.ringTimer invalidate];
            self.ringTimer = nil;
        }
        
        // 2.如果通话计时器不为空，销毁并置空
        if (self.callTimer) {
            NSLog(@"invalidate callTimer %@ %s", [self class], __FUNCTION__);
            [self.callTimer invalidate];
            self.callTimer = nil;
        }
        
        // 5.保存通话记录
        
        // 6.退出呼叫页面// 这里会关闭音视频的播放
        [self.dismissSubject sendNext:nil];
    });
}

/**
 停止响铃和震动
 */
- (void)stopRingAndVibrate
{
    if (self.vibrateTimer) {
        NSLog(@"invalidate vibrateTimer %@ %s", [self class], __FUNCTION__);
        [self.vibrateTimer invalidate];
        self.vibrateTimer = nil;
    }
    [self.stopRingSubject sendNext:nil];
    [self.stopVibrateSubject sendNext:nil];
}

#pragma mark -

// 是否插了耳机
- (BOOL)isHeadsetPluggedIn {
    AVAudioSessionRouteDescription* route = [[AVAudioSession sharedInstance] currentRoute];
    for (AVAudioSessionPortDescription* desc in [route outputs]) {
        if ([[desc portType] isEqualToString:AVAudioSessionPortHeadphones]) {
            if (self.isHandsFreeOn) {
                self.isHandsFreeOn = NO;
            }
            return YES;
        }
    }
    return NO;
}

- (void)audioRouteChangeListenerCallback:(NSNotification*)notification {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSDictionary *interuptionDict = notification.userInfo;
        NSLog(@"---------audioRouteChangeListenerCallback: %@", interuptionDict);
        NSInteger routeChangeReason = [[interuptionDict valueForKey:AVAudioSessionRouteChangeReasonKey] integerValue];
        switch (routeChangeReason) {
            case AVAudioSessionRouteChangeReasonNewDeviceAvailable:
                NSLog(@"插入耳机");
                if (self.handsFreeEnable) {
                    self.handsFreeEnable = NO;
                }
                if (self.isHandsFreeOn) {
                    self.isHandsFreeOn = NO;
                }
                break;
            case AVAudioSessionRouteChangeReasonOldDeviceUnavailable:
                NSLog(@"拔出耳机");
                if (!self.handsFreeEnable) {
                    self.handsFreeEnable = YES;
                }
                if (!self.isHandsFreeOn) {
                    self.isHandsFreeOn = YES;
                }
                break;
                
            default:
            {
                BOOL handsFreeEnable = ![self isHeadsetPluggedIn];
                if (self.handsFreeEnable != handsFreeEnable) {
                    self.handsFreeEnable = handsFreeEnable;
                }
            }
                break;
        }
    });
}

#pragma mark -
//获取设备当前网络IP地址
- (NSString *)getIPAddress:(BOOL)preferIPv4
{
    NSArray *searchArray = preferIPv4 ?
    @[ /*IOS_VPN @"/" IP_ADDR_IPv4, IOS_VPN @"/" IP_ADDR_IPv6,*/ IOS_WIFI @"/" IP_ADDR_IPv4, IOS_WIFI @"/" IP_ADDR_IPv6, IOS_CELLULAR @"/" IP_ADDR_IPv4, IOS_CELLULAR @"/" IP_ADDR_IPv6 ] :
    @[ /*IOS_VPN @"/" IP_ADDR_IPv6, IOS_VPN @"/" IP_ADDR_IPv4,*/ IOS_WIFI @"/" IP_ADDR_IPv6, IOS_WIFI @"/" IP_ADDR_IPv4, IOS_CELLULAR @"/" IP_ADDR_IPv6, IOS_CELLULAR @"/" IP_ADDR_IPv4 ] ;
    
    NSDictionary *addresses = [self getIPAddresses];
    NSLog(@"addresses: %@", addresses);
    
    __block NSString *address;
    [searchArray enumerateObjectsUsingBlock:^(NSString *key, NSUInteger idx, BOOL *stop)
     {
         address = addresses[key];
         if(address) *stop = YES;
     } ];
    return address ? address : @"0.0.0.0";
}

//获取所有相关IP信息
- (NSDictionary *)getIPAddresses
{
    NSMutableDictionary *addresses = [NSMutableDictionary dictionaryWithCapacity:8];
    
    // retrieve the current interfaces - returns 0 on success
    struct ifaddrs *interfaces;
    if(!getifaddrs(&interfaces)) {
        // Loop through linked list of interfaces
        struct ifaddrs *interface;
        for(interface=interfaces; interface; interface=interface->ifa_next) {
            if(!(interface->ifa_flags & IFF_UP) /* || (interface->ifa_flags & IFF_LOOPBACK) */ ) {
                continue; // deeply nested code harder to read
            }
            const struct sockaddr_in *addr = (const struct sockaddr_in*)interface->ifa_addr;
            char addrBuf[ MAX(INET_ADDRSTRLEN, INET6_ADDRSTRLEN) ];
            if(addr && (addr->sin_family==AF_INET || addr->sin_family==AF_INET6)) {
                NSString *name = [NSString stringWithUTF8String:interface->ifa_name];
                NSString *type;
                if(addr->sin_family == AF_INET) {
                    if(inet_ntop(AF_INET, &addr->sin_addr, addrBuf, INET_ADDRSTRLEN)) {
                        type = IP_ADDR_IPv4;
                    }
                } else {
                    const struct sockaddr_in6 *addr6 = (const struct sockaddr_in6*)interface->ifa_addr;
                    if(inet_ntop(AF_INET6, &addr6->sin6_addr, addrBuf, INET6_ADDRSTRLEN)) {
                        type = IP_ADDR_IPv6;
                    }
                }
                if(type) {
                    NSString *key = [NSString stringWithFormat:@"%@/%@", name, type];
                    addresses[key] = [NSString stringWithUTF8String:addrBuf];
                }
            }
        }
        // Free memory
        freeifaddrs(interfaces);
    }
    return [addresses count] ? addresses : nil;
}

@end
