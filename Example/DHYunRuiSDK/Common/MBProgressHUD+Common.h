//
//  MBProgressHUD+Common.h
//  AutomobileDataRecorder
//
//  Created by 王标 on 2017/10/10.
//  Copyright © 2017年 浙江大华技术股份有限公司. All rights reserved.
//

#import <MBProgressHUD/MBProgressHUD.h>

@interface MBProgressHUD (Common)

+ (MBProgressHUD *)showToast:(NSString *)toast;
+ (MBProgressHUD *)showToast:(NSString *)toast toView:(UIView *)view;

+ (MBProgressHUD *)showLoading;
+ (MBProgressHUD *)showLoadingToView:(UIView *)view;
+ (void)hideLoading;

@end
