//
//  SipMobileServerInfo.h
//  AFNetworking
//
//  Created by 蒋成龙 on 2020/4/15.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SipMobileServerInfo : NSObject

@property (nonatomic, copy)  NSString* account;
@property (nonatomic, assign)  NSInteger expireTime;
@property (nonatomic, assign)  NSInteger keepAliveTime;
@property (nonatomic, assign)  NSInteger localSipPort;
@property (nonatomic, copy)  NSString* primarySipServer;
@property (nonatomic, assign)  NSInteger serverSipPort;
@property (nonatomic, copy)  NSString* userAgent;

+ (instancetype)initWithJson:(NSString*)json;
+ (NSDictionary *)convertjsonStringToDict:(NSString *)jsonString;

- (NSString*)toJson;
@end

NS_ASSUME_NONNULL_END
