//
//  UIAlertController+SupportedInterfaceOrientations.m
//  Pods
//
//  Created by zyx on 17/5/18.
//
//

#import "UIAlertController+SupportedInterfaceOrientations.h"

@implementation UIAlertController (SupportedInterfaceOrientations)


- (UIInterfaceOrientationMask)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskAll;
}

- (BOOL)shouldAutorotate
{
    return true;
}

@end
