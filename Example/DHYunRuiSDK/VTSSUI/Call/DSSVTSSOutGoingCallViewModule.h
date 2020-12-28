//
//  DSSVTSSOutGoingCallViewModule.h
//  DSSUIModule
//
//  Created by 28404 on 2018/5/7.
//

#import <Foundation/Foundation.h>
#import <ReactiveObjC/RACSubject.h>

@interface DSSVTSSOutGoingCallViewModule : NSObject

/*************** 以下属性供RAC绑定，请勿外部设置 ***************/
@property (nonatomic, copy)   NSString *timeLabelText;      ///< timeLabel文字
@property (nonatomic, copy)   NSString *nameLabelText;      ///< nameLabel文字
@property (nonatomic, copy)   NSString *hanUpBtnText;       ///< 挂断按钮文字
@property (nonatomic, assign) BOOL isHandsFreenOn;          ///< 免提是否开启
@property (nonatomic, assign) BOOL isMuteOn;                ///< 静音是否开启
@property (nonatomic, assign) BOOL isHandsFreenHidden;      ///< 免提是否隐藏 YES-隐藏，NO-显示
@property (nonatomic, assign) BOOL isMuteHidden;            ///< 静音是否隐藏 YES-隐藏，NO-显示
@property (nonatomic, assign) BOOL isCallConnected;         ///< 呼叫是否已接通
@property (nonatomic) BOOL handsFreeEnable;   // 是否可以免提， 插入耳机的情况下不可以
@property (nonatomic, strong) RACSubject *dismissSubject;   ///< dismiss控制器subject
@property (nonatomic, strong) RACSubject *startTalkSubject; ///< 开始对讲subject
@property (nonatomic, strong) RACSubject *stopTalkSubject;  ///< 结束对讲subject
/*************** 以上属性供RAC绑定，请勿外部设置 ***************/

#pragma mark -

- (instancetype)initWithCommunityCode:(NSString *)code withUniqueKey:(NSString *)uniqueKey;

/**
 处理视图加载完成
 */
- (void)handleViewDidLoad;

/**
 处理静音
 */
- (void)handleMute;

/**
 处理免提
 */
- (void)handleHandsFree;

/**
 处理挂断电话
 */
- (void)handleHangUpCall;

#pragma mark - Notification
/**
 处理响铃通知
 @param notify NSNotification
 */
- (void)handleRingNotify:(NSNotification *)notify;

/**
 处理忙线通知
 @param notify NSNotification
 */
- (void)handleBusyNotify:(NSNotification *)notify;

/**
 处理对方接听通知
 @param notify NSNotification
 */
- (void)handleCallAnsweredNotify:(NSNotification *)notify;

/**
 处理被叫取消通知
 @param notify NSNotification
 */
- (void)handleCancelCallNotify:(NSNotification *)notify;

/**
 处理被叫结束通话
 @param notify NSNotification
 */
- (void)handleByeCallNotify:(NSNotification *)notify;

@end
