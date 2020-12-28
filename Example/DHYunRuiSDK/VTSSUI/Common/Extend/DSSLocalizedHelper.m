//
//  DSSLocalizedHelper.m
//  DSSClient
//
//  Created by xu_weifan on 17/7/31.
//  Copyright © 2017年 SDK. All rights reserved.
//

#import "DSSLocalizedHelper.h"

static NSMutableDictionary *bundleDictionary;

@implementation DSSLocalizedHelper

+ (NSBundle *)localizedBundleWithResourceBundle:(NSBundle *)resourceBundle {
    NSArray *allLanguages = [[NSUserDefaults standardUserDefaults] objectForKey:@"AppleLanguages"];
    NSString *lan = allLanguages.firstObject;
    NSString *resourceName = @"en";
    
    if ([lan hasPrefix:@"zh-Hans"]) {
        resourceName = @"zh-Hans";
    } else if ([lan hasPrefix:@"pt-BR"]) {
        resourceName = @"pt-BR";
    } else if ([lan hasPrefix:@"bg-CN"]) {
        resourceName = @"bg";
    } else if ([lan hasPrefix:@"zh-Hant"]) {
        resourceName = @"zh-Hant";
    }
    NSString *path = [resourceBundle pathForResource:resourceName ofType:@"lproj"];
    if (!path) {
        path = [resourceBundle pathForResource:@"en" ofType:@"lproj"];
    }
    return [NSBundle bundleWithPath:path];
}

+ (nullable NSString *)localizedStringForKey:(NSString * _Nonnull)key table:(nullable NSString *)tableName resourceBundle:(NSBundle * _Nonnull )resourceBundle {
    if (!key || !resourceBundle) {
//        NSAssert(NO, @"key或者resourceBundle不能为空,请确认传参无误");
        return key ?: @"";
    }
    if (!bundleDictionary) {
        bundleDictionary = [NSMutableDictionary dictionary];
    }
    NSBundle *bundle = bundleDictionary[[resourceBundle bundlePath]];
    if (!bundle) {
        bundle = [[self class] localizedBundleWithResourceBundle:resourceBundle];
        bundleDictionary[[resourceBundle bundlePath]] = bundle;
    }
    return [bundle localizedStringForKey:key value:nil table:tableName];
}

@end
