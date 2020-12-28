//
//  NSBundle+BundleForFrameworkModule.h
//  Pods
//
//  Created by zyx on 17/1/24.
//
//

#import <Foundation/Foundation.h>

@interface NSBundle (BundleForFrameworkModule)

+ (NSBundle*)bundleForFramework:(Class)frameworkClass module:(NSString*)module;
//通过bundle获取资源路径
+ (NSString *)bundleStrForFramework:(Class)frameworkClass module:(NSString *)module;
//通过bundle路径获取Image
+ (UIImage *)imageName:(NSString *)imageName bundleStrForFramework:(Class)frameworkClass module:(NSString *)module;
//按比例获取图片高度
+ (CGFloat)getHeightByImageName:(NSString *)imageName bundleStrForFramework:(Class)frameworkClass module:(NSString *)module;

@end
