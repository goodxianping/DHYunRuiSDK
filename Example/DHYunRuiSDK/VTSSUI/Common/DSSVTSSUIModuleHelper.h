//
//  DSSVTSSUIModuleHelper.h
//  Pods
//
//  Created by 28404 on 17/1/24.
//
//

#import <Foundation/Foundation.h>
#import <ReactiveObjC/ReactiveObjC.h>
#import <MBProgressHUD/MBProgressHUD.h>
#import "NSBundle+BundleForFrameworkModule.h"
#import "dssPubDefine.h"


#define VTSS_MAIN_COLOR [UIColor colorWithRed:74/255.0 green:146/255.0 blue:255/255.0 alpha:1.0]

#define BUNDLE_FOR_MODULE [NSBundle mainBundle]
#define IMAGE(image) [NSBundle imageName:image bundleStrForFramework:[self class] module:@"VTSS"]

// 错误提示

//MBProgress提示
#define MBPROGRESS_STRING(str, off) [DSSVTSSUIModuleHelper MBProgressString:str offset:off];

// loading
#define SHOW_LOADING() dispatch_async(dispatch_get_main_queue(), ^{\
[MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];\
});\

#define SHOW_LOADING_WITH_STRING(str) dispatch_async(dispatch_get_main_queue(), ^{\
MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];\
hud.label.text = str;\
});\

#define DISMISS_LOADING()  dispatch_async(dispatch_get_main_queue(), ^{\
[MBProgressHUD hideHUDForView:[UIApplication sharedApplication].keyWindow animated:YES];\
});\

FOUNDATION_EXTERN NSString *__nonnull const kJLUrlVTSS_Main;//VTSS模块(作为单独App)
FOUNDATION_EXTERN NSString *__nonnull const kJLUrlVTSS_Module_Main;//VTSS模块(作为模块)
FOUNDATION_EXTERN NSString *__nonnull const kJLUrlVTSS_Call;//VTSS被呼叫
FOUNDATION_EXTERN NSString *__nonnull const kJLUrlVTSS_CallManager;// 呼出

typedef NS_ENUM(NSInteger, VTSSMessageType) {
    VTSSMessageTypeAccess   = 0,    // 开门消息
    VTSSMessageTypeAlarm    = 1     // 报警消息
};

@interface DSSVTSSUIModuleHelper : NSObject
+ (void)MBProgressString:(nonnull NSString *)string offset:(NSInteger)offset;
+ (void)MBProgressCenterString:(nonnull NSString *)string;
@end
