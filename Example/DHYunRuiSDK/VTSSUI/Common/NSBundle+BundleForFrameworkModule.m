//
//  NSBundle+BundleForFrameworkModule.m
//  Pods
//
//  Created by zyx on 17/1/24.
//
//

#import "NSBundle+BundleForFrameworkModule.h"

@implementation NSBundle (BundleForFrameworkModule)

+ (NSBundle*)bundleForFramework:(Class)frameworkClass module:(NSString*)module {
    NSBundle *frameworkBundle = [NSBundle bundleForClass: frameworkClass];
    NSString* moduleBundlePath = [frameworkBundle pathForResource:module ofType:@"bundle"];
    return [NSBundle bundleWithPath:moduleBundlePath];
}
//通过bundle获取资源路径
+ (NSString *)bundleStrForFramework:(Class)frameworkClass module:(NSString *)module{
    NSBundle *bundle = [self bundleForFramework:frameworkClass module:module];
    NSString *bundleStr = [bundle resourcePath];
    return bundleStr;
}
//通过bundle路径获取Image
+ (UIImage *)imageName:(NSString *)imageName bundleStrForFramework:(Class)frameworkClass module:(NSString *)module{
    NSString *bundleStr = [self bundleStrForFramework:frameworkClass module:module];
    UIImage *image = [UIImage imageNamed:[NSString stringWithFormat:@"%@/%@",bundleStr,imageName]];
    return image;
}
//按比例获取图片高度
+ (CGFloat)getHeightByImageName:(NSString *)imageName bundleStrForFramework:(Class)frameworkClass module:(NSString *)module{
    UIImage *image = [self imageName:imageName bundleStrForFramework:frameworkClass module:module];
    CGFloat W = image.size.width;
    CGFloat H = image.size.height;
    CGFloat X = W / H;
    CGFloat height = [UIScreen mainScreen].bounds.size.width / X;
    return height;
}

@end
