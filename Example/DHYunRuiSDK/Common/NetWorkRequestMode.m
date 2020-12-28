//
//  NetWorkRequestMode.m
//  CloudSDK
//
//  Created by able on 2020/3/27.
//  Copyright © 2020 able. All rights reserved.
//

#import "NetWorkRequestMode.h"
@implementation NetWorkRequestMode

//#define http_ip "http://47.110.94.59"
#define http_ip "https://www.cloud-dahua.com"
+ (void)requestForTokenWithDic:(NSDictionary *)postDic success:(netWorkSuccessBlock)successBlock failed:(netWorkFailedBlock)failedBlock {
    NSString *urlbodyStr = [NSString stringWithFormat:@"/gateway/auth/oauth/token?grant_type=client_credentials&scope=server&client_id=%@&client_secret=%@",postDic[@"clent_id"],postDic[@"clent_secret"]];
    NSURL *requestUrl = [NSURL URLWithString:[NSString stringWithFormat:@"%s%@",http_ip,urlbodyStr]];
    
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:requestUrl];
    request.HTTPMethod = @"POST";
    [request setValue:@"application/x-www-form-urlencoded" forHTTPHeaderField:@"Content-Type"];
    
    NSURLSession *session = [NSURLSession sharedSession];
    
    NSURLSessionDataTask *dataTask = [session dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        
        dispatch_async(dispatch_get_main_queue(), ^{
            if (data != nil) {
                NSDictionary *jsonDic = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
                NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
                if (jsonDic[@"access_token"]) {
                    [userDefaults setValue:jsonDic[@"access_token"] forKey:@"access_token"];
                    [userDefaults synchronize];
                    if (successBlock) {
                        successBlock(jsonDic);
                    }
                } else {
                    if (failedBlock) failedBlock(error);
                }
            } else {
                if (failedBlock) failedBlock(error);
            }
        });
    }];
    
    [dataTask resume];
}

+ (NSData *)requestBodyWithParam:(NSDictionary *)postDic {
    
    if (![postDic isKindOfClass:[NSDictionary class]] || postDic.allKeys.count == 0) {
        return nil;
    }
    
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:postDic options:NSJSONWritingPrettyPrinted error:nil];
    return jsonData;
}

+ (NSString *)getToken {
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString *access_token = [userDefaults objectForKey:@"access_token"];
    return access_token;
}
@end

