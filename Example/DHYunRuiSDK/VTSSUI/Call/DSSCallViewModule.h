//
//  DSSCallViewModule.h
//  Pods
//
//  Created by 28404 on 2017/11/6.
//

#import <Foundation/Foundation.h>
#import <ReactiveObjC/RACSubject.h>
#import "DSSVTSSUIModuleHelper.h"
#import <DHSipSDK/DSSCallVTInfo.h>
#import <DHSipSDK/DSSChannelInfo.h>

@protocol DSSCallViewModuleDelegate

- (BOOL)isPlaying;
- (BOOL)isNetConnected;

@end

/**
 呼叫类型
 */
typedef NS_ENUM(NSInteger, CallStyle) {
    CallStyleAudioVideo = 0,        ///< 音频+视频
    CallStyleAudio      = 1,        ///< 音频
};

@interface DSSCallViewModule : NSObject
@property (nonatomic, weak) id delegate;
@property (nonatomic, strong) DSSInviteVTParam *inviteParam;               ///< 可视对讲参数
@property (nonatomic, strong, readonly) RACSubject *dismissSubject;     ///< dismiss控制器subject
@property (nonatomic, strong, readonly) RACSubject *startRingSubject;   ///< 开始响铃subject
@property (nonatomic, strong, readonly) RACSubject *stopRingSubject;    ///< 结束响铃subject
@property (nonatomic, strong, readonly) RACSubject *startVibrateSubject;///< 开始震动subject
@property (nonatomic, strong, readonly) RACSubject *stopVibrateSubject; ///< 结束震动subject
@property (nonatomic, strong, readonly) RACSubject *playVideoSubject;   ///< 播放视频subject
@property (nonatomic, strong, readonly) RACSubject *stopVideoSubject;   ///< 停止视频subject
@property (nonatomic, strong, readonly) RACSubject *openDoorSubject;    ///< 开门subject
@property (nonatomic, strong, readonly) RACSubject *startTalkSubject;   ///< 开始对讲subject
@property (nonatomic, strong, readonly) RACSubject *stopTalkSubject;    ///< 关闭对讲subject
/*************** 以下属性供RAC绑定，请勿外部设置 ***************/
@property (nonatomic, assign) BOOL refuseButtonHidden;              ///< 拒绝按钮(未接听)是否隐藏YES:隐藏，NO:显示
@property (nonatomic, assign) BOOL agreeButtonHidden;               ///< 接听按钮是否隐藏YES:隐藏，NO:显示
@property (nonatomic, assign) BOOL stopButtonHidden;                ///< 挂断(已接听)是否隐藏YES:隐藏，NO:显示
@property (nonatomic, assign) BOOL openDoorButtonHidden;            ///< 开门按钮是否隐藏YES:隐藏，NO:显示
@property (nonatomic, assign) BOOL authButtonHidden;                ///< 授权按钮是否隐藏YES:隐藏，NO:显示

@property (nonatomic, strong) DSSChannelInfo *playChannel;             ///< 播放视频通道
@property (nonatomic, strong) DSSChannelInfo *doorChannel;             ///< 门禁通道

@property (nonatomic, copy)   NSString *incomingLabelText;          ///< 通话时间 + 正在呼叫 label文字
@property (nonatomic, copy)   NSString *deviceNameLabelText;        ///< 设备名字label文字
@property (nonatomic, assign) int deviceProvider;                   ///< 设备厂商  0是未知 1是大华 2是海康
@property (nonatomic, assign) BOOL playWindowHidden;                ///< 播放窗口是否隐藏YES:隐藏，NO:显示
@property (nonatomic, assign) BOOL loadingVideoLabelHidden;         ///< 请求视屏中label是否隐藏YES:隐藏，NO:显示

@property (nonatomic, assign) BOOL canPlayVideo;                    ///< 是否可以播放视频：YES-可以，NO-不可以
@property (nonatomic, assign) BOOL isAgreed;                        ///< 是否已经接起电话 YES:已接起，NO:未接起
@property (nonatomic, assign) BOOL exchangeButtonHidden;            ///< 切换播放类型按钮是否隐藏 YES:隐藏，NO:显示 
@property (nonatomic, assign) CallStyle exchangedCallStyle;         ///< 切换来电类型(只有"音频+视频"这种来电类型可以切换)
@property (nonatomic, assign) BOOL isHandsFreeHidden;               ///< 免提按钮是否隐藏 YES:隐藏，NO:显示
@property (nonatomic, assign) BOOL isHandsFreeOn;                   ///< 免提是否开启 YES:开启，NO:关闭
@property (nonatomic, assign) BOOL isMuteHidden;                    ///< 静音按钮是否隐藏 YES:隐藏，NO:显示
@property (nonatomic, assign) BOOL isMuteOn;                        ///< 静音是否开启 YES:开启，NO:关闭
@property (nonatomic) BOOL handsFreeEnable;   // 是否可以免提， 插入耳机的情况下不可以

/**
* 是APP呼叫上来的？
*/
- (BOOL)isAPPCall;
/**
 * 恢复播放
 */
- (void)resumePlayVideo;

/**
授权
*/
- (void)authSuccess:(void (^)(void))successBack fail:(void (^)(NSError*))failBack;

/*************** 以上属性供RAC绑定，请勿外部设置 ***************/

/**
 处理视图加载完成
 */
- (void)handleViewDidLoad;

#pragma mark - Action
/**
 处理拒绝电话(未接听前)
 */
- (void)handleRefuseCall;

/**
 处理接听电话(同意)
 */
- (void)handleAgreeCall;

/**
 处理开门
 */
- (void)handleOpenDoor;

/**
 处理挂断电话(已接听后)
 */
- (void)handleCancelCall;

/**
 处理切换播放模式（音频 Or 音频+视频）
 */
- (void)handleExchangeCall;

/**
 处理静音
 */
- (void)handleMute;

/**
 处理免提
 */
- (void)handleHandsFree;

#pragma mark - Notification
/**
 处理第一帧到来
 */
- (void)handleFirstFrameArrive;

/**
 处理可视对讲音频会话ID回调
 */
- (void)handleAudioSessionIdCallBack:(NSString *)sessionId;

/**
 处理可视对讲音频端口回调
 */
- (void)handleAudioPortCallBack:(NSString *)port;

/**
 处理可视对讲视频会话ID回调
 */
- (void)handleVideoSessionIdCallBack:(NSString *)sessionId;

/**
 处理可视对讲视频端口回调
 */
- (void)handleVideoPortCallBack:(NSString *)port;

/**
 处理主叫取消通知（VTO取消呼叫或客户端接听超时）
 @param notify NSNotification
 */
- (void)handleCancelCallNofity:(NSNotification *)notify;

/**
 处理主叫结束通话通知（接通后VTO挂断）
 @param notify NSNotification
 */
- (void)handleByeCallNofity:(NSNotification *)notify;
@end
