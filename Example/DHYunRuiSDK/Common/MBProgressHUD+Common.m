//
//  MBProgressHUD+Common.m
//  AutomobileDataRecorder
//
//  Created by 王标 on 2017/10/10.
//  Copyright © 2017年 浙江大华技术股份有限公司. All rights reserved.
//

#import "MBProgressHUD+Common.h"

#define DefaultShowView [UIApplication sharedApplication].keyWindow

@implementation MBProgressHUD (Common)

+ (MBProgressHUD *)showToast:(NSString *)toast
{
    return [self showToast:toast toView:DefaultShowView];
}

+ (MBProgressHUD *)showToast:(NSString *)toast toView:(UIView *)view
{
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.detailsLabel.font = hud.label.font;
    hud.detailsLabel.text = toast;
    hud.removeFromSuperViewOnHide = YES;
    [hud hideAnimated:YES afterDelay:2.f];
    
    return hud;
}

+ (MBProgressHUD *)showLoading
{
    return [self showLoadingToView:DefaultShowView];
}

+ (MBProgressHUD *)showLoadingToView:(UIView *)view
{
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:view animated:YES];
    hud.removeFromSuperViewOnHide = YES;
    
    return hud;
}

+ (void)hideLoading
{
    [MBProgressHUD hideHUDForView:DefaultShowView animated:YES];
}

@end
