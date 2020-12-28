//
//  HttpAPI.h
//  AFNetworking
//
//  Created by 蒋成龙 on 2020/4/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HttpAPI : NSObject

+ (instancetype)shareInstance;

- (void)setHost:(NSString*)host;
- (void)setToken:(NSString*)token;
- (void)setUserID:(NSString*)userID;

@end

NS_ASSUME_NONNULL_END
