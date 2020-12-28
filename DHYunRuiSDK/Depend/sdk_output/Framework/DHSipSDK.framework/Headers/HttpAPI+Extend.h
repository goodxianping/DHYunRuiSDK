//
//  HttpAPI+Extend.h
//  AFNetworking
//
//  Created by 蒋成龙 on 2020/4/20.
//

#import <Foundation/Foundation.h>
#import "DSSChannelInfo.h"
#import "HttpAPI.h"

NS_ASSUME_NONNULL_BEGIN

@interface HttpAPI (Extend)

- (void)queryChannelInfo:(NSDictionary*)disParam success:(void (^)(DSSChannelInfo*))successBack fail:(void (^)(NSError*))failBack;

- (void)openDoor:(NSDictionary*)disParam success:(void (^)(void))successBack fail:(void (^)(NSError*))failBack;

- (void)auth:(NSDictionary*)disParam success:(void (^)(void))successBack fail:(void (^)(NSError*))failBack;

@end

NS_ASSUME_NONNULL_END
