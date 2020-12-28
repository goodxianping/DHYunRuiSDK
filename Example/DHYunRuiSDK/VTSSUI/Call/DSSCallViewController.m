//
//  DSSCallViewController.m
//  Pods
//
//  Created by 28404 on 2017/11/6.
//

#import <AVFoundation/AVFoundation.h>
#import <CoreTelephony/CTCallCenter.h>
#import <CoreTelephony/CTCall.h>
#import <MediaPlayer/MediaPlayer.h>
#import <DHMediaPlay/DHMediaPlay-swift.h>
#import <AFNetworking/AFNetworking.h>
#import "dssPubDefine.h"
#import "DSSVTSSUIModuleHelper.h"
#import "DSSCallViewController.h"
#import "DSSCallButton.h"
#import <DHSipSDK/RemoteNotifyDefine.h>



#define CALL_MAIN_FUNC_BUTTON_HEIGHT 75
#define CALL_SUB_FUNC_BUTTON_HEIGHT 65

@interface DSSCallViewController () <DHPlayListenerProtocol, DHTalkListenerProtocol, DSSCallViewModuleDelegate>
@property (weak, nonatomic) IBOutlet UIImageView *bgImageView;

@property (weak, nonatomic) IBOutlet DSSCallButton *agreeButton;      ///< 接听
@property (weak, nonatomic) IBOutlet DSSCallButton *refuseButton;     ///< 拒绝
@property (weak, nonatomic) IBOutlet DSSCallButton *openDoorButton;   ///< 开锁
@property (weak, nonatomic) IBOutlet DSSCallButton *stopButton;       ///< 结束通话
@property (weak, nonatomic) IBOutlet DSSCallButton *muteButton;       ///< 静音按钮
@property (weak, nonatomic) IBOutlet DSSCallButton *handsFreeButton;  ///< 免提按钮
@property (weak, nonatomic) IBOutlet DSSCallButton *exchagneButton;   ///< 切换按钮
@property (weak, nonatomic) IBOutlet DSSCallButton *authButton;       ///< 授权

@property (weak, nonatomic) IBOutlet NSLayoutConstraint *openDoorRightLayout;             ///< 开门按钮距离父视图右边布局
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *openDoorCenterXLayout;           ///< 开门按钮在父视图x居中布局
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *handsFreeCenterXLayout;          ///< 免提按钮在父视图x居中布局
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *handsFreeCenterOpenDoorLayout;   ///< 免提按钮与开门按钮居中对齐布局


@property (weak, nonatomic) IBOutlet DHMediaPlayView *playWindow;        ///< 播放窗口
@property (weak, nonatomic) IBOutlet UILabel *deviceNameLabel;        ///< 设备名字
@property (weak, nonatomic) IBOutlet UILabel *incommingLabel;         ///< 通话时间 + 正在呼叫
@property (weak, nonatomic) IBOutlet UILabel *loadingVideoLabel;      ///< 请求视屏中

@property (strong, nonatomic) AVAudioPlayer *ringPlayer;                ///< 响铃播放器
@property (strong, nonatomic) DHMediaPlayView *playWindow2;                ///< 对讲窗口

@property (nonatomic, strong) CTCallCenter *callCenter;

@end


@implementation DSSCallViewController
{
    CTCallCenter *_callCenter;
    BOOL _isNetConnected;
}

+ (UIViewController *)getViewController{
    DSSCallViewController *vc = [[DSSCallViewController alloc]init];
    return vc;
}

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    if (nibNameOrNil == nil && nibBundleOrNil == nil) {
        self = [super initWithNibName:NSStringFromClass([self class]) bundle:BUNDLE_FOR_MODULE];
    } else {
        self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    }
    _viewModule = [[DSSCallViewModule alloc] init];
    _viewModule.delegate = self;
    return self;
}

- (void)configNotification:(NSNotification *)notification{
     _viewModule.inviteParam = notification.object;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(stopVTCall:) name:VT_CALL_ACTION_EVENT_STOP object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(cancellVTCall:) name:VT_CALL_ACTION_EVENT_CANCEL object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(byeVTCall:) name:VT_CALL_ACTION_EVENT_BYE object:nil];
    
    [self setUpRingPlayer];
    [self initUI];
    self.playWindow2 = [[DHMediaPlayView alloc] initWithFrame:CGRectMake(0, 0, 20, 20)];
    self.playWindow2.hidden = YES;
    
    [self.playWindow addPlayListener:self];
    [self.playWindow2 addTalkListener:self];
    self.playWindow.userInteractionEnabled = NO;
    [self.playWindow setDefultSplitNumber:1];
    [self.playWindow setAllBtnHidden:0 hidden:YES];
    
    [self bindSignal];
    [self.viewModule handleViewDidLoad];
    
    [self receiveCallBlock];
    
    AFNetworkReachabilityManager *manager = [AFNetworkReachabilityManager sharedManager];
    AFNetworkReachabilityStatus status = manager.networkReachabilityStatus;
    _isNetConnected = (status != AFNetworkReachabilityStatusNotReachable);
    [self networkListenerBlock];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;
    AVAudioSession *avAudioSession = [AVAudioSession sharedInstance];
//    [avAudioSession setCategory: AVAudioSessionCategoryPlayAndRecord error:nil];
     [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDuckOthers error:nil];
    [avAudioSession setActive:YES error:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
    selector:@selector(unActiveApp:)
    name:UIApplicationWillResignActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
    selector:@selector(activeApp:)
    name:UIApplicationDidBecomeActiveNotification object:nil];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleDefault;
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)setEnableTalk {
    AVAudioSession *avAudioSession = [AVAudioSession sharedInstance];
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDuckOthers error:nil];
    [avAudioSession setActive:true error:nil];
    if (self.viewModule.isAgreed && self.playWindow2) {
        if (!self.muteButton.selected) {
            [self.playWindow2 stopSampleAudio:0];
            [self.playWindow2 startSampleAudio:0];
            [self.playWindow2 startTalkSound:0];
        } else {
            [self.playWindow2 startSampleAudio:0];
            [self.playWindow2 stopSampleAudio:0];
        }
    }
}

- (void)refuse {
    if (!self.refuseButton.hidden) {
        [self.viewModule handleRefuseCall];
    } else {
        [self.viewModule handleCancelCall];
    }
}

- (void)receiveCallBlock {
    __weak typeof(self) weakself = self;
    CTCallCenter *callCenter = [[CTCallCenter alloc] init];
    callCenter.callEventHandler = ^(CTCall* call) {
        if ([call.callState isEqualToString:CTCallStateDisconnected])
        {
            NSLog(@"挂断电话Call has been disconnected");
            //            [weakself refuse];
        }
        else if ([call.callState isEqualToString:CTCallStateConnected])
        {
            NSLog(@"电话通了Call has just been connected");
            [weakself refuse];
        }
        else if([call.callState isEqualToString:CTCallStateIncoming])
        {
            NSLog(@"来电话了Call is incoming");
            //            [weakself refuse];
            
        }
        else if ([call.callState isEqualToString:CTCallStateDialing])
        {
            NSLog(@"正在拨出电话call is dialing");
            [weakself refuse];
        }
        else
        {
            NSLog(@"什么没做Nothing is done");
        }
    };
    _callCenter = callCenter;
}

- (void)initUI
{
    [self.agreeButton setTitle:_T(@"Accept", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    [self.refuseButton setTitle:_T(@"Hang up", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    [self.openDoorButton setTitle:_T(@"Open Door", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    [self.authButton setTitle:_T(@"Auth", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    [self.stopButton setTitle:_T(@"Hang up", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    
    [self.muteButton setTitle:_T(@"Mute", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    [self.handsFreeButton setTitle:_T(@"Hands-free", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    
    [self.agreeButton setImageWidth:CALL_MAIN_FUNC_BUTTON_HEIGHT andImageHeight:CALL_MAIN_FUNC_BUTTON_HEIGHT];
    [self.refuseButton setImageWidth:CALL_MAIN_FUNC_BUTTON_HEIGHT andImageHeight:CALL_MAIN_FUNC_BUTTON_HEIGHT];
    [self.openDoorButton setImageWidth:CALL_MAIN_FUNC_BUTTON_HEIGHT andImageHeight:CALL_MAIN_FUNC_BUTTON_HEIGHT];
    [self.authButton setImageWidth:CALL_MAIN_FUNC_BUTTON_HEIGHT andImageHeight:CALL_MAIN_FUNC_BUTTON_HEIGHT];
    [self.stopButton setImageWidth:CALL_MAIN_FUNC_BUTTON_HEIGHT andImageHeight:CALL_MAIN_FUNC_BUTTON_HEIGHT];

    [self.muteButton setImageWidth:CALL_SUB_FUNC_BUTTON_HEIGHT andImageHeight:CALL_SUB_FUNC_BUTTON_HEIGHT];
    [self.handsFreeButton setImageWidth:CALL_SUB_FUNC_BUTTON_HEIGHT andImageHeight:CALL_SUB_FUNC_BUTTON_HEIGHT];
    [self.exchagneButton setImageWidth:CALL_SUB_FUNC_BUTTON_HEIGHT andImageHeight:CALL_SUB_FUNC_BUTTON_HEIGHT];
    self.openDoorButton.hidden  = YES;
    self.authButton.hidden      = YES;
    if ([_viewModule isAPPCall]) {
        self.playWindow.hidden      = YES;
        self.loadingVideoLabel.hidden = YES;
        self.exchagneButton.hidden  = YES;
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)dealloc
{
    DISMISS_LOADING();
    [[NSNotificationCenter defaultCenter] removeObserver:self name:VT_CALL_ACTION_EVENT_STOP object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:VT_CALL_ACTION_EVENT_CANCEL object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:VT_CALL_ACTION_EVENT_BYE object:nil];
    NSLog(@"=============CALL in dealloc");
}

- (void)setUpRingPlayer
{
    NSString *path = [[NSBundle mainBundle] pathForResource:@"vtss_ring_tone" ofType:@"m4r"];
    _ringPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:[NSURL fileURLWithPath:path] error:nil];
    _ringPlayer.numberOfLoops = -1;
    [_ringPlayer prepareToPlay];
}

- (void)networkListenerBlock {
    __weak typeof(self) weakself = self;
    AFNetworkReachabilityManager *manager = [AFNetworkReachabilityManager sharedManager];
    [manager startMonitoring];
    [manager setReachabilityStatusChangeBlock:^(AFNetworkReachabilityStatus status) {
        if (status == AFNetworkReachabilityStatusNotReachable) {
            [weakself handleWhenNetNotReachable];
        } else if (status == AFNetworkReachabilityStatusReachableViaWWAN || status == AFNetworkReachabilityStatusReachableViaWiFi) {
            [weakself handleWhenNetReConnected];
        }
    }];
}

- (void)unActiveApp:(NSNotification *)_notification {
    AFNetworkReachabilityManager *manager = [AFNetworkReachabilityManager sharedManager];
    [manager stopMonitoring];
    [self.playWindow stop:0];
    if (self.viewModule.isAgreed && self.playWindow2) {
        if (!self.muteButton.selected) {
            [self.playWindow2 startTalkSound:0];
        }
    }
}

- (void)activeApp:(NSNotification *)_notification {
    AFNetworkReachabilityManager *manager = [AFNetworkReachabilityManager sharedManager];
    [manager startMonitoring];
    [self.viewModule resumePlayVideo];
    [self setEnableTalk];
}

- (void)handleWhenNetNotReachable {
    if (!_isNetConnected) {
        return;
    }
    NSLog(_T(@"network_error", BUNDLE_FOR_MODULE));
    _isNetConnected = NO;
    NSLog(@"============= 网络断开，停止视频");
    [self.playWindow stop:0];
}

- (void)handleWhenNetReConnected {
    if (_isNetConnected) {
        return;
    }
    _isNetConnected = YES;
    NSLog(@"============= 网络连接，开始恢复播放视频");
    [self.viewModule resumePlayVideo];
}

#pragma mark - 绑定信号
- (void)bindSignal
{
    [self bindAction];
    [self bindRACSubject];
    [self bindViewModuleSignal];
}

- (void)setVolume:(float) volume {
    MPVolumeView* volumeView  = [[MPVolumeView alloc] init];
    UISlider *volumeViewSlider = nil;
    for (UIView *view in [volumeView subviews]) {
        if ([view.class.description isEqualToString:@"MPVolumeSlider"]) {
            volumeViewSlider = (UISlider *)view;
            break;
        }
    }
    if (volumeViewSlider) {
        dispatch_async(dispatch_get_main_queue(), ^{
            // change system volume, the value is between 0.0f and 1.0f
            [volumeViewSlider setValue:volume animated:NO];
            // send UI control event to make the change effect right now. 立即生效
            [volumeViewSlider sendActionsForControlEvents:UIControlEventTouchUpInside];
        });
    }
    
}

- (void)bindAction
{
    @weakify(self)
    [[self.agreeButton rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        [self.viewModule handleAgreeCall];
    }];
    [[self.refuseButton rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        [self.viewModule handleRefuseCall];
    }];
    [[self.openDoorButton rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        [self openDoorAlert];
    }];
    [[self.authButton rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        SHOW_LOADING();
        // 开门操作

        [self.viewModule authSuccess:^{
            DISMISS_LOADING();
            NSLog(_T(@"Auth successfully", BUNDLE_FOR_MODULE));
        } fail:^(NSError *_error) {
            DISMISS_LOADING();
            NSLog(_T(@"Failed to auth", BUNDLE_FOR_MODULE));
        }];
    }];
    [[self.stopButton rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        [self.viewModule handleCancelCall];
    }];
    // 点击静音开关
    [[self.muteButton rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        self.muteButton.selected = !self.muteButton.selected;
        NSLog(@"-----------点击静音按钮前category：%@", [AVAudioSession sharedInstance].category);
        NSLog(@"-----------点击静音按钮前categoryOptions：%lu", (unsigned long)(long)[AVAudioSession sharedInstance].categoryOptions);
        float outputVolume = [[AVAudioSession sharedInstance] outputVolume];
        if (self.muteButton.selected) {
            [self.playWindow2 stopSampleAudio:0];
        } else {
            [self.playWindow2 startSampleAudio:0];
        }
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            NSError *error;
            NSLog(@"-----------点击静音按钮后start category：%@", [AVAudioSession sharedInstance].category);
            if ([AVAudioSession sharedInstance].category != AVAudioSessionCategoryPlayAndRecord) {
                 [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDuckOthers error:&error];
            }
            NSLog(@"-----------点击静音按钮后end category：%@", [AVAudioSession sharedInstance].category);
            NSLog(@"-----------点击静音按钮前outputVolume：%f", outputVolume);
            [self setVolume:outputVolume];
            NSLog(@"-----------点击静音按钮后111 category：%@", [AVAudioSession sharedInstance].category);
            NSLog(@"-----------点击静音按钮后111 categoryOptions：%lu", (unsigned long)(long)[AVAudioSession sharedInstance].categoryOptions);

            if ([AVAudioSession sharedInstance].category != AVAudioSessionCategoryPlayAndRecord) {
                [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:&error];
            }
            NSLog(@"-----------点击静音按钮切换category，error:%@", error.description);
            NSLog(@"-----------点击静音按钮后222 category：%@", [AVAudioSession sharedInstance].category);
            NSLog(@"-----------点击静音按钮后222 categoryOptions：%lu", (unsigned long)(long)[AVAudioSession sharedInstance].categoryOptions);
            NSLog(@"-----------点击静音按钮后333 isHandsFreeOn：%d", self.viewModule.isHandsFreeOn);
            if (self.viewModule.isHandsFreeOn) {
                [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:&error];
                NSLog(@"------------点击静音按钮，切换听筒模式-免提，error：%@", error.description);
            } else {
                [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideNone error:&error];
                NSLog(@"------------点击静音按钮，切换听筒模式-听筒，error：%@", error.description);
            }
        });
        
    }];
    [[self.handsFreeButton rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        [self.viewModule handleHandsFree];
    }];
    [[self.exchagneButton rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        [self.viewModule handleExchangeCall];
    }];
}

// 开门
- (void)openDoorAlert
{
    __block typeof(self) weakSelf = self;
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:_T(@"Are you sure to unlock?", BUNDLE_FOR_MODULE) message:@"" preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *openDoorAction = [UIAlertAction actionWithTitle:_T(@"Continue to unlock", BUNDLE_FOR_MODULE) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [weakSelf openDoorExe];
    }];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:_T(@"Cancel", BUNDLE_FOR_MODULE) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [alert dismissViewControllerAnimated:YES completion:nil];
    }];
    [alert addAction:cancelAction];
    [alert addAction:openDoorAction];
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)openDoorExe
{
    SHOW_LOADING();
    // 开门操作
    [self.viewModule.openDoorSubject subscribeError:^(NSError * _Nullable error) {
        DISMISS_LOADING();
        NSLog(_T(@"Failed to open door", BUNDLE_FOR_MODULE));
    } completed:^{
        DISMISS_LOADING();
        NSLog(_T(@"Opened door successfully", BUNDLE_FOR_MODULE));
    }];
    [self.viewModule handleOpenDoor];
}

- (void)bindRACSubject
{
    @weakify(self)
    // dismissViewController
    [self.viewModule.dismissSubject subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        NSLog(@"=============关闭界面 停止播放");
        [self.playWindow stop:0];
        [self.playWindow2 stopTalk:0];
        [self.playWindow removePlayListener:self];
        [self.playWindow2 removeTalkListener:self];
        // 这里测试提了一个bug DTS000318182
        // 在微信通话期间， 进入APP收到门口机呼叫，接通之后，微信挂断了，手机顶部依然会有红条（显示微信通话）
        // 这个时候其实对APP的布局是有印象的 如果这个时候挂断APP，会导致RN主界面的底部的tab恢复不了，有一半顶到底下去了。
        // 可能是dismissViewControllerAnimated这个方法导致的
        // 这里将这个方法异步执行， 这样在它执行前， stopTalk之后， 让RN布局先自动恢复
        dispatch_async(dispatch_get_main_queue(), ^{
            [self dismissViewControllerAnimated:YES completion:^{
                NSLog(@"The call is over.");
            }];
        });
    }];
    
    // 开始响铃
    [self.viewModule.startRingSubject subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        if (self.ringPlayer && ![self.ringPlayer isPlaying]) {
            [self.ringPlayer play];
        }
    }];
    
    // 停止响铃
    [self.viewModule.stopRingSubject subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        [self.ringPlayer stop];
        self.ringPlayer = nil;
    }];
    
    // 开始震动
    [self.viewModule.startVibrateSubject subscribeNext:^(id  _Nullable x) {
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
    }];
    
    // 停止震动
    [self.viewModule.stopVibrateSubject subscribeNext:^(id  _Nullable x) {
        AudioServicesDisposeSystemSoundID(kSystemSoundID_Vibrate);
    }];
    
    // 开始播放视频
    [self.viewModule.playVideoSubject subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        dispatch_async(dispatch_get_main_queue(), ^{
            NSLog(@"=============播放视频");
            Camera *camera = (Camera *)x;
            [self.playWindow addCamera:camera at:0 recordType:self.viewModule.deviceProvider];
            BOOL r = [self.playWindow play:0];
            BOOL r2 = [self.playWindow closeAudio:0];
            NSLog(@"%d", r);
            NSLog(@"%d", r2);
        });
        
    }];
    
    // 结束播放视频
    [self.viewModule.stopVideoSubject subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        dispatch_async(dispatch_get_main_queue(), ^{
            NSLog(@"=============停止播放视频");
            [self.playWindow stop:0];
        });
    }];
    
    // 开始对讲
    [self.viewModule.startTalkSubject subscribeNext:^(RtpOUdpTalkCamera *camera) {
        @strongify(self)
        [[AVAudioSession sharedInstance] requestRecordPermission:^(BOOL isOpen) {
            if (!isOpen) {
                NSLog(@"Please turn on microphone permissions in system Settings.");
            }
        }];
        [self.playWindow2 stopTalk:0];
        [self.playWindow2 addCamera:camera at:0 recordType:self.viewModule.deviceProvider];
        BOOL r = [self.playWindow2 startTalk:0];
        NSError *error;
//        if ([AVAudioSession sharedInstance].category != AVAudioSessionCategoryPlayAndRecord) {
//           [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:&error];
//        }
        [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryMultiRoute error:&error];
        [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:&error];
        NSLog(@"%d", r);
    }];
    
    // 结束对讲
    [self.viewModule.stopTalkSubject subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        [self.playWindow2 stopTalk:0];
    }];
}

- (void)bindViewModuleSignal
{
    if (![self.viewModule isAPPCall]) {
        RAC(self.exchagneButton, hidden) = RACObserve(self.viewModule, exchangeButtonHidden);
        RAC(self.playWindow, hidden) = RACObserve(self.viewModule, playWindowHidden);
        RAC(self.openDoorButton, hidden) = RACObserve(self.viewModule, openDoorButtonHidden);
        RAC(self.authButton, hidden) = RACObserve(self.viewModule, authButtonHidden);
    }
    RAC(self.agreeButton, hidden) = RACObserve(self.viewModule, agreeButtonHidden);
    RAC(self.refuseButton, hidden) = RACObserve(self.viewModule, refuseButtonHidden);
    RAC(self.stopButton, hidden) = RACObserve(self.viewModule, stopButtonHidden);
    RAC(self.muteButton, hidden) = RACObserve(self.viewModule, isMuteHidden);
    RAC(self.handsFreeButton, hidden) = RACObserve(self.viewModule, isHandsFreeHidden);
    self.loadingVideoLabel.hidden = YES;
    
    RAC(self.deviceNameLabel, text) = RACObserve(self.viewModule, deviceNameLabelText);
    RAC(self.incommingLabel, text) = RACObserve(self.viewModule, incomingLabelText);
    
    @weakify(self)
    [RACObserve(self.viewModule, canPlayVideo) subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        BOOL canPlayVideo = [x boolValue];
        self.handsFreeCenterXLayout.priority = canPlayVideo ? UILayoutPriorityDefaultHigh : UILayoutPriorityDefaultLow;
        self.handsFreeCenterOpenDoorLayout.priority = canPlayVideo ? UILayoutPriorityDefaultLow : UILayoutPriorityDefaultHigh;
    }];
    
    [RACObserve(self.viewModule, isAgreed) subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        BOOL isAgreed = [x boolValue];
        self.openDoorRightLayout.priority = isAgreed ? UILayoutPriorityDefaultHigh : UILayoutPriorityDefaultLow;
        self.openDoorCenterXLayout.priority = isAgreed ? UILayoutPriorityDefaultLow : UILayoutPriorityDefaultHigh;
    }];
    
    [RACObserve(self.viewModule, exchangedCallStyle) subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        CallStyle style = [x integerValue];
        
        NSString *exchangeTitle = (style == CallStyleAudioVideo) ? _T(@"Voice Answer", BUNDLE_FOR_MODULE) : _T(@"Video Answer", BUNDLE_FOR_MODULE);
        UIImage *exchangeImageNormal = (style == CallStyleAudioVideo) ? [UIImage imageNamed:@"hujiao_yuyinjieting_nor.png"] : [UIImage imageNamed:@"hujiao_shipinjieting_nor.png"];
        UIImage *exchangeImageHighlighted = (style == CallStyleAudioVideo) ? [UIImage imageNamed:@"hujiao_yuyinjieting_hov.png"] : [UIImage imageNamed:@"hujiao_shipinjieting_hov.png"] ;
        [self.exchagneButton setTitle:exchangeTitle  forState:UIControlStateNormal];
        [self.exchagneButton setImage:exchangeImageNormal forState:UIControlStateNormal];
        [self.exchagneButton setImage:exchangeImageHighlighted  forState:UIControlStateHighlighted];
        
    }];
    // 点击免提
    [RACObserve(self.viewModule, isHandsFreeOn) subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        BOOL isHandsFreeOn = [x boolValue];
        self.handsFreeButton.selected = isHandsFreeOn;
        float outputVolume = [[AVAudioSession sharedInstance] outputVolume];
        NSLog(@"-----------点击免提按钮前的category：%@", [AVAudioSession sharedInstance].category);
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.03 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            NSError *error;
            if ([AVAudioSession sharedInstance].category != AVAudioSessionCategoryPlayAndRecord) {
                [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDuckOthers error:&error];
            }
            if (isHandsFreeOn) {
                [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:&error];
                NSLog(@"-----------点击免提按钮，切换听筒模式-免提，error：%@", error.description);
            } else {
                [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideNone error:&error];
                NSLog(@"-----------点击免提按钮，切换听筒模式-听筒，error：%@", error.description);
            }
            NSLog(@"-----------点击免提按钮后的category：%@", [AVAudioSession sharedInstance].category);
            [self setVolume:outputVolume];
        });
    }];
    
    // 免提是否可点
    [RACObserve(self.viewModule, handsFreeEnable) subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        self.handsFreeButton.enabled = [x boolValue];
    }];
}

#pragma mark - Notification
- (void)stopVTCall:(NSNotification *)notification
{
    // 参照老版本，此种情况未处理
    [self.viewModule handleCancelCall];
}

- (void)cancellVTCall:(NSNotification *)notification
{
    [self.viewModule handleCancelCallNofity:notification];
}

- (void)byeVTCall:(NSNotification *)notification
{
    [self.viewModule handleByeCallNofity:notification];
}

#pragma mark - DHPlayListenerProtocol

- (void)onPlayeStatusCallback:(NSUInteger)winIndex status:(enum PlayStatusType)status code:(NSInteger)code
{
    __block typeof(self) weakSelf = self;
    if (status == PlayStatusTypeEPlayFirstFrame) {
        dispatch_async(dispatch_get_main_queue(), ^{
            NSLog(@"=============播放handleFirstFrameArrive");
            [weakSelf.viewModule handleFirstFrameArrive];
            [self.playWindow setSpeakerAutoEnable: false];
            self.viewModule.isHandsFreeOn = self.handsFreeButton.selected;
        });
    } else if (status == PlayStatusTypeENetworkaAbort) {
        dispatch_async(dispatch_get_main_queue(), ^{
            NSLog(@"=============播放错误 播放停止");
            [self.playWindow stop:winIndex];
        });
    }
}

#pragma mark - DHTalkListenerProtocol

- (void)onTalkResult:(NSUInteger)winIndex result:(enum TalkResultType)result code:(NSInteger)code{
    NSString *codeStr = [NSString stringWithFormat:@"%ld",(long)code];
    if (result == TalkResultTypeETalkAudioSessionId) {
        [self.viewModule handleAudioSessionIdCallBack:codeStr];
    } else if (result == TalkResultTypeETalkAudioPort) {
        [self.viewModule handleAudioPortCallBack:codeStr];
    } else if (result == TalkResultTypeETalkVideoSessionId) {
        [self.viewModule handleVideoSessionIdCallBack:codeStr];
    } else if (result == TalkResultTypeETalkVideoPort) {
        [self.viewModule handleVideoPortCallBack:codeStr];
    } else if (result == TalkResultTypeETalkSuccess) {
        NSLog(@"Enabled video intercom successfully");
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.playWindow2 setSpeakerAutoEnable: false];
            self.viewModule.isHandsFreeOn = self.handsFreeButton.selected;
        });
    } else if (result == TalkResultTypeETalkFailed) {
        NSLog(@"Failed to enable video intercom");
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.playWindow2 stopTalk:0];
        });
    }
}

#pragma mark -

- (BOOL)isPlaying {
    return [self.playWindow isPlaying:0];
}

- (BOOL)isNetConnected {
    return _isNetConnected;
}

@end
