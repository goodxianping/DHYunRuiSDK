//
//  DSSVTSSOutGoingCallViewController.m
//  DSSUIModule
//
//  Created by 28404 on 2018/5/7.
//

#import <AVFoundation/AVFoundation.h>
#import "DSSVTSSUIModuleHelper.h"
#import "DSSVTSSOutGoingCallViewController.h"
#import "DSSCallButton.h"
#import <CoreTelephony/CTCallCenter.h>
#import <CoreTelephony/CTCall.h>
#import "AFNetworking.h"
#import <AFNetworkReachabilityManager.h>
#import <DHMediaPlay/DHMediaPlay-swift.h>
#import <DHSipSDK/RemoteNotifyDefine.h>
#import "dssPubDefine.h"
#import <AFNetworkReachabilityManager.h>

#define CALL_OUT_MAIN_FUNC_BUTTON_HEIGHT 75
#define CALL_OUT_SUB_FUNC_BUTTON_HEIGHT 65

@interface DSSVTSSOutGoingCallViewController () <DHTalkListenerProtocol>
@property (weak, nonatomic) IBOutlet DHMediaPlayView *playWindow;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) IBOutlet UILabel *timeLabel;
@property (weak, nonatomic) IBOutlet DSSCallButton *muteBtn;  // 静音
@property (weak, nonatomic) IBOutlet DSSCallButton *handsFreeBtn; // 免提
@property (weak, nonatomic) IBOutlet DSSCallButton *hangUpBtn; // 挂断
@end

@implementation DSSVTSSOutGoingCallViewController
{
    CTCallCenter *_callCenter;
}

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    if (nibNameOrNil == nil && nibBundleOrNil == nil) {
        self = [super initWithNibName:NSStringFromClass([self class]) bundle:BUNDLE_FOR_MODULE];
    } else {
        self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initUI];
    [self.playWindow addTalkListener:self];
    
    [self bindSignal];
    [self.viewModule handleViewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(stopVTCall:) name:VT_CALL_ACTION_EVENT_STOP object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(cancellVTCall:) name:VT_CALL_ACTION_EVENT_CANCEL object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(byeVTCall:) name:VT_CALL_ACTION_EVENT_BYE object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(callRing:) name:VT_CALL_ACTION_EVENT_RING object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(callBusy:) name:VT_CALL_ACTION_EVENT_BUSY object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(callAnswered:) name:VT_CALL_ACTION_MESSAGE_START object:nil];
    
    [self receiveCallBlock];
    [self networkListenerBlock];
}


- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;
    AVAudioSession *avAudioSession = [AVAudioSession sharedInstance];
    [avAudioSession setCategory: AVAudioSessionCategoryPlayAndRecord error:nil];
    [avAudioSession setActive:YES error:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillEnterForeground)name:UIApplicationWillEnterForegroundNotification object:nil];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleDefault;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:VT_CALL_ACTION_EVENT_STOP object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:VT_CALL_ACTION_EVENT_CANCEL object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:VT_CALL_ACTION_EVENT_BYE object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:VT_CALL_ACTION_EVENT_RING object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:VT_CALL_ACTION_EVENT_BUSY object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:VT_CALL_ACTION_MESSAGE_START object:nil];
    [self.playWindow stopTalk:0];
    NSLog(@"=============CALL out dealloc");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)applicationWillEnterForeground {
    AVAudioSession *avAudioSession = [AVAudioSession sharedInstance];
     [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDuckOthers error:nil];
    [avAudioSession setActive:true error:nil];
    if (self.viewModule.isCallConnected && self.playWindow) {
        if (!self.muteBtn.selected) {
            [self.playWindow stopSampleAudio:0];
            [self.playWindow startSampleAudio:0];
        } else {
            [self.playWindow startSampleAudio:0];
            [self.playWindow stopSampleAudio:0];
        }
    }
}

- (void)refuse {
     [self.viewModule handleHangUpCall];
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

- (void)networkListenerBlock {
    __weak typeof(self) weakself = self;
    AFNetworkReachabilityManager *manager = [AFNetworkReachabilityManager sharedManager];
    [manager startMonitoring];
    [manager setReachabilityStatusChangeBlock:^(AFNetworkReachabilityStatus status) {
        if (status == AFNetworkReachabilityStatusNotReachable) {
            [weakself handleWhenNetNotReachable]; // 这里会内存泄露， 改成函数调用
        } else if (status == AFNetworkReachabilityStatusReachableViaWWAN || status == AFNetworkReachabilityStatusReachableViaWiFi) {
            [weakself handleWhenNetReConnected];
        }
    }];
}

- (void)handleWhenNetNotReachable {
    NSLog(_T(@"network_error", BUNDLE_FOR_MODULE));
}

- (void)handleWhenNetReConnected {
    
}

- (void)initUI {
    [self.muteBtn setTitle:_T(@"Mute", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    [self.handsFreeBtn setTitle:_T(@"Hands-free", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    [self.hangUpBtn setTitle:_T(@"Hang up", BUNDLE_FOR_MODULE) forState:UIControlStateNormal];
    
    [self.muteBtn setImageWidth:CALL_OUT_SUB_FUNC_BUTTON_HEIGHT andImageHeight:CALL_OUT_SUB_FUNC_BUTTON_HEIGHT];
    [self.handsFreeBtn setImageWidth:CALL_OUT_SUB_FUNC_BUTTON_HEIGHT andImageHeight:CALL_OUT_SUB_FUNC_BUTTON_HEIGHT];
    [self.hangUpBtn setImageWidth:CALL_OUT_MAIN_FUNC_BUTTON_HEIGHT andImageHeight:CALL_OUT_MAIN_FUNC_BUTTON_HEIGHT];
}

- (void)bindSignal {
    RAC(self.nameLabel, text) = RACObserve(self.viewModule, nameLabelText);
    RAC(self.timeLabel, text) = RACObserve(self.viewModule, timeLabelText);
    RAC(self.handsFreeBtn, hidden) = RACObserve(self.viewModule, isHandsFreenHidden);
    RAC(self.muteBtn, hidden) = RACObserve(self.viewModule, isMuteHidden);
    RAC(self.hangUpBtn.titleLabel, text) = RACObserve(self.viewModule, hanUpBtnText);
    
    @weakify(self)
    // 免提
    [RACObserve(self.viewModule, isHandsFreenOn) subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        BOOL isHandsFreeOn = [x boolValue];
        self.handsFreeBtn.selected = isHandsFreeOn;
        
        NSLog(@"-----------点击免提按钮前的category：%@", [AVAudioSession sharedInstance].category);
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.03 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            NSError *error;
            if ([AVAudioSession sharedInstance].category != AVAudioSessionCategoryPlayAndRecord) {
                [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:&error];
            }
            if (isHandsFreeOn) {
                [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:&error];
                NSLog(@"-----------点击免提按钮，切换听筒模式-免提，error：%@", error.description);
            } else {
                [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideNone error:&error];
                NSLog(@"-----------点击免提按钮，切换听筒模式-听筒，error：%@", error.description);
            }
            NSLog(@"-----------点击免提按钮后的category：%@", [AVAudioSession sharedInstance].category);
        });
    }];
    
    // 免提是否可点
    [RACObserve(self.viewModule, handsFreeEnable) subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        self.handsFreeBtn.enabled = [x boolValue];
    }];
    
    // 点击静音
    [[self.muteBtn rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        self.muteBtn.selected = !self.muteBtn.selected;
        NSLog(@"-----------点击静音按钮前category：%@", [AVAudioSession sharedInstance].category);
        NSLog(@"-----------点击静音按钮前categoryOptions：%lu", (unsigned long)(long)[AVAudioSession sharedInstance].categoryOptions);
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.03 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            if (self.muteBtn.selected) {
                [self.playWindow stopSampleAudio:0];
            } else {
                [self.playWindow startSampleAudio:0];
            }
            NSLog(@"-----------点击静音按钮后111 category：%@", [AVAudioSession sharedInstance].category);
            NSLog(@"-----------点击静音按钮后111 categoryOptions：%lu", (unsigned long)(long)[AVAudioSession sharedInstance].categoryOptions);
            
            NSError *error;
            
            if ([AVAudioSession sharedInstance].category != AVAudioSessionCategoryPlayAndRecord) {
                [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord error:&error];
            }
            
            NSLog(@"-----------点击静音按钮切换category，error:%@", error.description);
            NSLog(@"-----------点击静音按钮后222 category：%@", [AVAudioSession sharedInstance].category);
            NSLog(@"-----------点击静音按钮后222 categoryOptions：%lu", (unsigned long)(long)[AVAudioSession sharedInstance].categoryOptions);
            
            if (self.viewModule.isHandsFreenOn) {
                [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:&error];
                NSLog(@"------------点击静音按钮，切换听筒模式-免提，error：%@", error.description);
            } else {
                [[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideNone error:&error];
                NSLog(@"------------点击静音按钮，切换听筒模式-听筒，error：%@", error.description);
            }
        });
    }];
    
    
    // 点击免提
    [[self.handsFreeBtn rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        [self.viewModule handleHandsFree];
    }];
    
    // 点击挂断
    [[self.hangUpBtn rac_signalForControlEvents:UIControlEventTouchUpInside] subscribeNext:^(__kindof UIControl * _Nullable x) {
        @strongify(self)
        [self.viewModule handleHangUpCall];
    }];
    
    // dismiss控制器
    [self.viewModule.dismissSubject subscribeError:^(NSError * _Nullable error) {
        @strongify(self)
        NSLog(error.localizedDescription);
        dispatch_async(dispatch_get_main_queue(), ^{
            [self dismissViewControllerAnimated:YES completion:^{
                [[AVAudioSession sharedInstance] setActive:NO withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation error:nil];
            }];
        });
    } completed:^{
        @strongify(self)
        NSLog(@"The call is over.");
        dispatch_async(dispatch_get_main_queue(), ^{
            [self dismissViewControllerAnimated:YES completion:^{
                [[AVAudioSession sharedInstance] setActive:NO withOptions:AVAudioSessionSetActiveOptionNotifyOthersOnDeactivation error:nil];
            }];
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
        [self.playWindow stopTalk:0];
        [self.playWindow addCamera:camera at:0 recordType:0];
        BOOL r = [self.playWindow startTalk:0];
        NSLog(@"%d", r);
    }];
    
    // 结束对讲
    [self.viewModule.stopTalkSubject subscribeNext:^(id  _Nullable x) {
        @strongify(self)
        [self.playWindow stopTalk:0];
    }];
}

#pragma mark - Notification
- (void)callRing:(NSNotification *)notification {
    [self.viewModule handleRingNotify:notification];
}

- (void)callBusy:(NSNotification *)notification {
    [self.viewModule handleBusyNotify:notification];
}

- (void)callAnswered:(NSNotification *)notification {
    [self.viewModule handleCallAnsweredNotify:notification];
}

- (void)stopVTCall:(NSNotification *)notification {
    // 参照老版本，此种情况未处理
    [self.viewModule handleByeCallNotify:notification];
}

- (void)cancellVTCall:(NSNotification *)notification {
    [self.viewModule handleCancelCallNotify:notification];
}

- (void)byeVTCall:(NSNotification *)notification {
    [self.viewModule handleByeCallNotify:notification];
}

#pragma mark - DHTalkListenerProtocol

- (void)onTalkResult:(NSUInteger)winIndex result:(enum TalkResultType)result code:(NSInteger)code{
    if (result == TalkResultTypeETalkSuccess) {
        NSLog(@"Enabled talk successfully");
        dispatch_async(dispatch_get_main_queue(), ^{
            [self.playWindow setSpeakerAutoEnable: false];
        });
    } else if (result == TalkResultTypeETalkFailed) {
        NSLog(@"Failed to talk");
        [self.playWindow stopTalk:0];
    }
}

@end
