//
//  DHDataCenter.m
//  DHYunRuiSDK_Example
//
//  Created by Li_JinLin on 2020/7/17.
//  Copyright © 2020 starryKey. All rights reserved.
//

#import "DHDataCenter.h"

@implementation DHDataCenter

static DHDataCenter *dataCenter = nil;

+ (instancetype)shareInstance{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        dataCenter = [[DHDataCenter alloc] init];
    });
    return dataCenter;
}

@end
