//
//  DHDataCenter.h
//  DHYunRuiSDK_Example
//
//  Created by Li_JinLin on 2020/7/17.
//  Copyright © 2020 starryKey. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DHDataCenter : NSObject

@property(nonatomic, copy)NSString *token;           //登录鉴权
@property(nonatomic, copy)NSString *communityCode;   //小区编码
@property(nonatomic, copy)NSString *userId;
@property(nonatomic, copy)NSString *serviceHost;
@property(nonatomic, copy)NSString *companyID;
@property(nonatomic, copy)NSString *personFileID;
@property(nonatomic, copy)NSString *phoneNumber;
@property(nonatomic, copy)NSString *lcToken;        //播放视频用

+ (instancetype)shareInstance;

@end

