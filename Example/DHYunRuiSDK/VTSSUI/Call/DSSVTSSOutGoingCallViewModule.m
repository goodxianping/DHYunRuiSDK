//
//  DSSVTSSOutGoingCallViewModule.m
//  DSSUIModule
//
//  Created by 28404 on 2018/5/7.
//

#import "DSSVTSSOutGoingCallViewModule.h"
#import <AVFoundation/AVFoundation.h>
#import <DHMediaPlay/DHMediaPlay-swift.h>
#import "DSSVTSSUIModuleHelper.h"
#import <DHSipSDK/DSSCallVTInfo.h>
#import "dssPubDefine.h"
#import <DHSipSDK/SipManager.h>

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
static NSTimeInterval maxCallTime = 60 * 2;   ///< 最大通话时长

@interface DSSVTSSOutGoingCallViewModule ()

@property (nonatomic, copy) NSString *communityCode;
@property (nonatomic, copy) NSString *uniqueKey;
@property (nonatomic, retain) NSTimer *ringTimer;           ///< 响铃计时器
@property (nonatomic, assign) NSInteger ringTimeInterval;   ///< 响铃正计时
@property (nonatomic, retain) NSTimer *callTimer;           ///< 通话计时器
@property (nonatomic, assign) NSInteger callTimeInterval;   ///< 通话正计时
@property (nonatomic, retain) NSDate *startDate;            ///< 呼叫开始时间 存储通话记录用。呼出时间，如果接通，改为接通时间

@property (nonatomic, strong) DSSRingVtCallParam *ringVtCallParam;     ///< 响铃信息,在对端响铃的通知中可以获取到
@property (nonatomic, strong) DSSStartVtCallMsgParam *startVtCallMsg;  ///< 可视对讲邀请信息，在对端接通的时候可以获取到
@property (nonatomic, strong) RtpOUdpTalkCamera *rtpSipTalkCamera;///< 对讲camera

@end

@implementation DSSVTSSOutGoingCallViewModule

- (instancetype)initWithCommunityCode:(NSString *)code withUniqueKey:(NSString *)uniqueKey {
    if (self = [super init]) {
        [self setUp];
        _communityCode = code;
        _uniqueKey = uniqueKey;
    }
    return self;
}

- (instancetype)init {
    if (self = [super init]) {
        [self setUp];
    }
    return self;
}

- (void)setUp {
    _timeLabelText = _T(@"Calling...", BUNDLE_FOR_MODULE);
    _hanUpBtnText = _T(@"Cancel", BUNDLE_FOR_MODULE);
    _isHandsFreenOn = YES;
    _ringTimeInterval = 0;
    _isHandsFreenHidden = YES;
    _isMuteHidden = YES;
    _dismissSubject = [RACSubject subject];
    _startTalkSubject = [RACSubject subject];
    _stopTalkSubject = [RACSubject subject];
    BOOL handsFreeEnable = ![self isHeadsetPluggedIn];
    if (self.handsFreeEnable != handsFreeEnable) {
        self.handsFreeEnable = handsFreeEnable;
    }
    [self registerNotification];
}

- (void)registerNotification {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(audioRouteChangeListenerCallback:)   name:AVAudioSessionRouteChangeNotification object:nil];//设置通知
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillTerminateNotification:)   name:UIApplicationWillTerminateNotification object:nil];//设置通知
}

- (void)dealloc {
    NSLog(@"dealloc");
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

/**
 处理视图加载完成
 */
- (void)handleViewDidLoad {
    /** 呼叫流程
     *  1、startVTCall
     *  2、等对端回调startVTCall消息
     *  3、startTalk,传入aport,vport,callid,dlgid
     */
    self.startDate = [NSDate date];
    [self configViewModule];
    [self handleStartVTCall];
}

/**
 处理静音
 */
- (void)handleMute {
    self.isMuteOn = !self.isMuteOn;
}

/**
 处理免提
 */
- (void)handleHandsFree {
    self.isHandsFreenOn = !self.isHandsFreenOn;
}

/**
 处理挂断电话
 */
- (void)handleHangUpCall {
    [self doCommonOperationAfterStopCall];
    if (self.isCallConnected) {
        [self handleStopVTCall];
    } else {
        [self handleCancelVTCall];
    }
    [self.dismissSubject sendCompleted];
}

#pragma mark - Notification
/**
 处理对端响铃通知
 @param notify NSNotification
 */
- (void)handleRingNotify:(NSNotification *)notify {
    // Ring通知回来的数据中的userId、callId、dlgId在stop、cancel中要用到
    // 此处存起来
    DSSRingVtCallParam *ringVtCallParam = notify.object;
    self.ringVtCallParam = ringVtCallParam;
}

/**
 处理对方忙线通知
 @param notify NSNotification
 */
- (void)handleBusyNotify:(NSNotification *)notify {
    __block typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf doCommonOperationAfterStopCall];
        NSError *error = [NSError errorWithDomain:@"dahuatech.com.vtss" code:0 userInfo:@{NSLocalizedDescriptionKey : _T(@"The number you dialed is busy now.", BUNDLE_FOR_MODULE)}];
        [weakSelf.dismissSubject sendError:error];
    });
}

/**
 处理对方接听通知
 @param notify NSNotification
 */
- (void)handleCallAnsweredNotify:(NSNotification *)notify {
    DSSStartVtCallMsgParam *param = notify.object;
    // 如果返回的端口为0，则不处理
    if (param.rtpAudioPort == 0) {
        return;
    }
    __block typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        weakSelf.hanUpBtnText = _T(@"Hang up", BUNDLE_FOR_MODULE);
        weakSelf.isHandsFreenHidden = NO;
        weakSelf.isMuteHidden = NO;
        weakSelf.isCallConnected = YES;
        weakSelf.startDate = [NSDate date];
        weakSelf.startVtCallMsg = notify.object;
        if (weakSelf.ringTimer) {
            [weakSelf.ringTimer invalidate];
            weakSelf.ringTimer = nil;
        }
        weakSelf.callTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:weakSelf selector:@selector(callTimerCheck:) userInfo:nil repeats:YES];
        [weakSelf startTalk];
    });
}

/**
 处理被叫取消通知（没接通）
 @param notify NSNotification
 */
- (void)handleCancelCallNotify:(NSNotification *)notify {
    __block typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        NSError *error = [NSError errorWithDomain:@"dahuatech.com.vtss" code:0 userInfo:@{NSLocalizedDescriptionKey : _T(@"The number you dialed is busy now.", BUNDLE_FOR_MODULE)}];
        [weakSelf doCommonOperationAfterStopCall];
        [weakSelf.dismissSubject sendError:error];
    });
}

/**
 处理被叫结束通话
 @param notify NSNotification
 */
- (void)handleByeCallNotify:(NSNotification *)notify {
    __block typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf doCommonOperationAfterStopCall];
        [weakSelf.dismissSubject sendCompleted];
    });
}

#pragma mark - Private
- (void)configViewModule {
    self.nameLabelText = _T(@"Management Center", BUNDLE_FOR_MODULE);
}

// 开始呼叫
// TODO：这些参数是否需要修改
- (void)handleStartVTCall {
    self.ringTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(ringTimerCheck:) userInfo:nil repeats:YES];
    [[SipManager shareInstance] Calling:self.uniqueKey phoneNumber:self.communityCode communityCode:self.communityCode];
}

// 呼叫接通之后 开始对讲
- (void)startTalk {
    // 组装camera
    self.rtpSipTalkCamera = [[RtpOUdpTalkCamera alloc] init];
    self.rtpSipTalkCamera.callType = self.startVtCallMsg.callType;
    self.rtpSipTalkCamera.port = self.startVtCallMsg.rtpAudioPort;
    self.rtpSipTalkCamera.vPort = self.startVtCallMsg.rtpVideoPort;
    self.rtpSipTalkCamera.userId = self.startVtCallMsg.userID;
    self.rtpSipTalkCamera.callId = self.startVtCallMsg.callID;
    self.rtpSipTalkCamera.dlgId = self.startVtCallMsg.dialogID;
    self.rtpSipTalkCamera.tId = self.startVtCallMsg.tID;
    self.rtpSipTalkCamera.sampleDepth = self.startVtCallMsg.audioBits;
    self.rtpSipTalkCamera.sampleRate = self.startVtCallMsg.sampleRate;
    self.rtpSipTalkCamera.localIp = [self getIPAddress:true];
    self.rtpSipTalkCamera.isCall = YES;
    self.rtpSipTalkCamera.serverIp = self.startVtCallMsg.sipIp;           ///< RTP地址
    [self.startTalkSubject sendNext:self.rtpSipTalkCamera];

}


/**
 处理取消呼叫(被叫接听前)
 */
- (void)handleCancelVTCall {
    NSLog(@"handleCancelCall %@ %s", [self class], __FUNCTION__);
    [[SipManager shareInstance] HangUpCallingWithKey:self.ringVtCallParam.key withCid:self.ringVtCallParam.cid];
}

/**
 处理取消呼叫(被叫接听后)
 */
- (void)handleStopVTCall {
    [[SipManager shareInstance] HangUpCallingWithKey:self.ringVtCallParam.key withCid:self.ringVtCallParam.cid];
}

- (void)ringTimerCheck:(NSTimer *)timer {
    self.ringTimeInterval ++;
    self.timeLabelText = [NSString stringWithFormat:@"00:%02ld", (long)self.ringTimeInterval];
    if (self.ringTimeInterval >= maxRingTime) {
        [timer invalidate];
        timer = nil;
        [self doCommonOperationAfterStopCall];
        [self handleCancelVTCall];
        NSError *error = [NSError errorWithDomain:@"dahuatech.com.vtss" code:0 userInfo:@{NSLocalizedDescriptionKey : _T(@"The number you dialed is not answered for the moment.", BUNDLE_FOR_MODULE)}];
        [self.dismissSubject sendError:error];
    }
}

- (void)callTimerCheck:(NSTimer *)timer {
    self.callTimeInterval ++;
    self.timeLabelText = [NSString stringWithFormat:@"%02ld:%02ld", (long)self.callTimeInterval/60, (long)self.callTimeInterval%60];
    if (self.callTimeInterval >= maxCallTime) {
        [timer invalidate];
        timer = nil;
        [self doCommonOperationAfterStopCall];
        [self handleStopVTCall];
        [self.dismissSubject sendCompleted];
    }
}

// 在呼叫停止后执行的通用操作
- (void)doCommonOperationAfterStopCall {
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
    
    // 3.如果是可以播放视频的通话，结束通话
    if (self.isCallConnected) {
        NSLog(@"stopTalk %@ %s", [self class], __FUNCTION__);
        [self.stopTalkSubject sendNext:nil];
    }
}

#pragma mark -

// 是否插了耳机
- (BOOL)isHeadsetPluggedIn {
    AVAudioSessionRouteDescription* route = [[AVAudioSession sharedInstance] currentRoute];
    for (AVAudioSessionPortDescription* desc in [route outputs]) {
        if ([[desc portType] isEqualToString:AVAudioSessionPortHeadphones]) {
            if (self.isHandsFreenOn) {
                self.isHandsFreenOn = NO;
            }
            return YES;
        }
    }
    return NO;
}

- (void)audioRouteChangeListenerCallback:(NSNotification*)notification {
    typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        NSDictionary *interuptionDict = notification.userInfo;
        NSInteger routeChangeReason = [[interuptionDict valueForKey:AVAudioSessionRouteChangeReasonKey] integerValue];
        switch (routeChangeReason) {
            case AVAudioSessionRouteChangeReasonNewDeviceAvailable:
                NSLog(@"插入耳机");
                if (weakSelf.handsFreeEnable) {
                    weakSelf.handsFreeEnable = NO;
                }
                if (weakSelf.isHandsFreenOn) {
                    weakSelf.isHandsFreenOn = NO;
                }
                break;
            case AVAudioSessionRouteChangeReasonOldDeviceUnavailable:
                NSLog(@"拔出耳机");
                if (!weakSelf.handsFreeEnable) {
                    weakSelf.handsFreeEnable = YES;
                }
                if (!weakSelf.isHandsFreenOn) {
                    weakSelf.isHandsFreenOn = YES;
                }
                break;
                
            default:
            {
                BOOL handsFreeEnable = ![weakSelf isHeadsetPluggedIn];
                if (weakSelf.handsFreeEnable != handsFreeEnable) {
                    weakSelf.handsFreeEnable = handsFreeEnable;
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
