//
//  OCSipComponent.h
//  SIPStackComponent
//
//  Created by Chenjian on 2019/5/5.
//  Copyright © 2019年 Dahua. All rights reserved.
//

#ifndef OCSipComponent_h
#define OCSipComponent_h
#import "OCSipListener.h"

//日志等级
typedef NS_ENUM(NSInteger, E_LOG_LEVEL)
{
    LOGLEVEL_FATAL,     //致命错误
    LOGLEVEL_ERR,       //错误
    LOGLEVEL_WARNING,   //可能导致出错
    LOGLEVEL_INFO,      //当前运行状态
    LOGLEVEL_DEBUG,     //详细调试信息
    LOGLEVEL_ALL,       //所有日志信息
};

@interface OCSipComponent : NSObject

- (instancetype)init;
- (instancetype)initWithSipIndex:(NSInteger)index;
- (void) setSipIndex:(NSInteger)index;
- (NSInteger) getSipIndex;
- (BOOL) setSipProxyInfo: (NSString*)sipServerInfo;
- (BOOL) setHeader: (NSString*)sipHeader;
- (void) addInviteHeader:(NSString *)key Value:(NSString *)value;
- (BOOL) setCallInfo: (NSString*)callInfo;
- (void) setSipListener: (id<OCSipListener>)sipLis;
- (int) start;
- (int) stop;
- (void) SipServerInfoChanged;
- (void) CallingWithPhoneNumber: (NSString*)phoneNumber;
- (void) ReCallingWithCid: (int)cid;
- (void) AcceptCallingWithCid: (int)acceptCid;

- (void) RejectCallingWithCid: (int)rejectCid;
- (void) RejectDisturbWithCid: (int)rejectCid;
- (void) RejectNoAuthWithCid:(int)rejectCid;
/*
 * status:403 486 488
 */
- (void) RejectCalling:(int)rejectCid status:(int)status;

- (void) HangUpCallingWithCid: (int)cid;
- (void) OpenDoorWithCid: (int)cid passwd:(NSString*)passwd;
- (NSString*) getSipServerInfo;
- (void) stopVideo: (int)cid;
- (void) setOptionListener: (id<OCSipListener>)sipLis;
- (void) sendOption: (NSString*)uri callInfo:(NSString*)callInfo;
- (void) startRegister;
- (void) unRegister;
- (void) setToUri: (NSString*)uri;
- (void) setPAI: (NSString *)pai;
- (void) setMobileLogLevel:(E_LOG_LEVEL)logLevel logTag:(NSString*)logTag;
+ (void) destroyThreadPool;

- (void) setFlag:(BOOL)toChange;
@end
#endif /* OCSipComponent_h */
