//
//  Easy4ipSDK_LoginManagerListener.h
//  Easy4ipSDK
//
//  Created by yang_pengwei on 2017/10/30.
//  Copyright © 2017年 www.dahuatech.com. All rights reserved.
//

#ifndef __LCOpenSDK_LCOpenSDK_LoginManagerListener_H__
#define __LCOpenSDK_LCOpenSDK_LoginManagerListener_H__
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol LCOpenSDK_LoginManagerListener <NSObject>

/**
 netsdk   断线
 @param deviceSn 序列号
 */
- (void)onNetSDKDisconnect:(NSString *)deviceSn devType:(NSInteger)devType;

/**
 login result
 @param type 1 :初始化 2:预打洞 3:预登录 --参考枚举 OC_LOGIN_STATE
 @param DeviceSn 序列号 初始化时为空字符串
 @param code 错误码
 */
- (int)onLoginResult:(NSInteger)type DeviceSn:(NSString*)deviceSn Code:(NSInteger)code devType:(NSInteger)devType NetDeviceInfoEx:(NSString*)netDeviceInfoEx;

- (void)onP2PLogInfo:(NSString *)jsonStr;

@end

#endif /* __LCOpenSDK_LCOpenSDK_LoginManagerListener_H__ */
