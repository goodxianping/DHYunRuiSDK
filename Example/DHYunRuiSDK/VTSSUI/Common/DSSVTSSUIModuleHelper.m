//
//  DSSVTSSUIModuleHelper.m
//  Pods
//
//  Created by 28404 on 17/1/24.
//
//

#import "DSSVTSSUIModuleHelper.h"

@implementation DSSVTSSUIModuleHelper

+ (void)MBProgressString:(nonnull NSString *)string offset:(NSInteger)offset
{
    dispatch_async(dispatch_get_main_queue(), ^{
        MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];
        hud.mode = MBProgressHUDModeText;
        hud.label.text = string;
        hud.offset = CGPointMake(0, offset);
        [hud hideAnimated:YES afterDelay:2.0];
    });
}

+ (void)MBProgressCenterString:(nonnull NSString *)string {
    dispatch_async(dispatch_get_main_queue(), ^{
        MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:[UIApplication sharedApplication].keyWindow animated:YES];
        hud.mode = MBProgressHUDModeText;
        hud.bezelView.style = MBProgressHUDBackgroundStyleSolidColor;
        
//        hud.backgroundColor = [UIColor colorWithWhite:0 alpha:0.6];
        hud.bezelView.backgroundColor = [UIColor blackColor];
        hud.label.textColor = [UIColor whiteColor];
        hud.label.text = string;
        hud.margin = 10.0f;
        [hud hideAnimated:YES afterDelay:2.0];
    });
}
@end
