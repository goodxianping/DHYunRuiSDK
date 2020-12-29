//
//  HttpClient.h
//  ReactNativeBase
//
//  Created by huang_yundi on 2018/1/29.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^successBlock)(id data);
typedef void(^failBlock)(NSError* error);

@interface HttpClient : NSObject

@property (copy, atomic) NSString* host;
@property (copy, atomic) NSString* userID;
@property (copy, atomic) NSString* token;

+ (instancetype)shareInstance;

- (void)post:(NSString*)method params:(NSDictionary*)dicParam success:(successBlock)suBlock fail:(failBlock)faBlock;

- (void)get:(NSString*)method params:(NSDictionary*)dicParam success:(successBlock)suBlock fail:(failBlock)faBlock;

@end
