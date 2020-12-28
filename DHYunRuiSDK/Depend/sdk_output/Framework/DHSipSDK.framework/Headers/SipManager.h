//
//  SipManager.h
//  AFNetworking
//
//  Created by 蒋成龙 on 2020/4/15.
//

#import <Foundation/Foundation.h>
#import "SipMobileServerInfo.h"

NS_ASSUME_NONNULL_BEGIN
extern NSString* sAPPClientType;

@interface SipManager : NSObject

+ (SipManager*)shareInstance;

+ (void) destroyThreadPool;

/// 添加SIP服务
/// @param info SIP详情
/// @param uniqueKey 唯一标识（用于区分不同的SIP）
/// @param isNeedChanged 是否需要变化(云为YES)
- (void) addSipserver:(SipMobileServerInfo*)info withKey:(NSString*)uniqueKey changeContact:(BOOL) isNeedChanged;

/// 通过key移除SIP
/// @param uniqueKey 唯一表识
- (void) removeByKey:(NSString*)uniqueKey;

/// 移除全部
- (void) removeAll;

/// 发起呼叫
/// @param uniqueKey 唯一标识
/// @param phoneNumber 电话号码
/// @param communityCode 社区编码
- (void) Calling:(NSString*)uniqueKey phoneNumber:(NSString*)phoneNumber communityCode:(NSString*)communityCode;

/// 重新呼叫
/// @param uniqueKey 唯一标识
/// @param cid sip标识
- (void) ReCallingWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;

/// 接听
/// @param uniqueKey 唯一标识
/// @param cid sip标识
- (void) AcceptCallingWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;

/// 拒接
/// @param uniqueKey 唯一标识
/// @param cid sip标识
- (void) RejectCallingWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;
- (void) RejectDisturbWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;
- (void) RejectNoAuthWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;

/// 主动挂断
/// @param uniqueKey 唯一标识
/// @param cid sip标识
- (void) HangUpCallingWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;

- (void) OpenDoorWithKey:(NSString*)uniqueKey passwd:(NSString*)passwd withCid: (NSInteger)cid;

@end

NS_ASSUME_NONNULL_END
