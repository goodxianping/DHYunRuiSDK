//
//  DSSLocalizedHelper.h
//  DSSClient
//
//  Created by xu_weifan on 17/7/31.
//  Copyright © 2017年 SDK. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DSSLocalizedHelper : NSObject

+ (nullable NSString *)localizedStringForKey:(NSString * _Nonnull)key table:(nullable NSString *)tableName resourceBundle:(NSBundle * _Nonnull )resourceBundle;

@end
