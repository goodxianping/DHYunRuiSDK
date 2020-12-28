//
//  UIViewController+InterfaceOrientation.m
//  Pods
//
//  Created by xu_weifan on 17/4/25.
//
//

#import "UIViewController+InterfaceOrientation.h"
#import <objc/runtime.h>

@implementation UIViewController (InterfaceOrientation)

+ (void)load {

}

- (BOOL)dss_shouldAutorotate {
    return NO;
}

@end
