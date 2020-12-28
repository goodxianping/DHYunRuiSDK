//
//  LCSDK_RestApi.h
//  LCSDK
//
//  Created by zhou_yuepeng on 16/9/13.
//  Copyright © 2016年 com.lechange.lcsdk. All rights reserved.
//

#ifndef LCOpenSDK_RestApiParameter_h
#define LCOpenSDK_RestApiParameter_h
#import <Foundation/Foundation.h>

@interface LCOpenSDK_RestApiParameter : NSObject

@property (nonatomic, copy) NSString  *host;
@property (nonatomic)       NSUInteger port;
@property (nonatomic, copy) NSString  *clientType;
@property (nonatomic, copy) NSString  *clientID;
@property (nonatomic, copy) NSString  *clientVersion;
@property (nonatomic, copy) NSString  *project;
@property (nonatomic, copy) NSString  *pushID;
@property (nonatomic, copy) NSString  *authUserName;
@property (nonatomic, copy) NSString  *authPassWordMd5;

/* add for APP 3.3 */
@property (nonatomic, copy) NSString  *clientOV;
@property (nonatomic, copy) NSString  *clientOS;
@property (nonatomic, copy) NSString  *terminalModel;
@property (nonatomic, copy) NSString  *terminalId;
@property (nonatomic, copy) NSString  *language;
@property (nonatomic, copy) NSString  *clientProtoVersion;

/* add for Saas*/
@property (nonatomic, copy) NSString  *appId;
@property (nonatomic) NSInteger  isHttps;
@property (nonatomic, copy) NSString  *caPath;
@property (nonatomic) NSInteger  isUserCa;

- (NSString*)toJSONString;
@end

@interface LCOpenSDK_RestApiParameterManager : NSObject

+ (LCOpenSDK_RestApiParameterManager*)shareMyInstance;
/**
 *  初始化HsviewClient RestApi
 *
 *  @param parameter 初始化参数(参考LCOpenSDK_RestApiParameter定义)
 *
 *  @return YES/NO 成功/失败
 */
- (BOOL)initRestWithParameter:(LCOpenSDK_RestApiParameter*)parameter;

/**
 *  反初始化RestApi参数
 */
- (void)uninitRestParameter;

- (LCOpenSDK_RestApiParameter*)getRestApiParameter;

@end

#endif /* LCOpenSDK_RestApiParameter_h */
