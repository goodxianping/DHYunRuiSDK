//
//  NetWorkRequestMode.h
//  CloudSDK
//
//  Created by able on 2020/3/27.
//  Copyright © 2020 able. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NetWorkRequestMode : NSObject
/** 网络成功回调block */
typedef void(^netWorkSuccessBlock)(NSDictionary *resultDic);

/** 网络失败回调block */
typedef void(^netWorkFailedBlock)(NSError *error);

//获取token
+ (void)requestForTokenWithDic:(NSDictionary *)postDic success:(netWorkSuccessBlock)successBlock failed:(netWorkFailedBlock)failedBlock;

@end

NS_ASSUME_NONNULL_END
