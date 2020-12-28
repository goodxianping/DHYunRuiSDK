//
//  UIViewController+BaseStyle.m
//  DSSUIModule
//
//  Created by xu_weifan on 2017/11/25.
//

#import "UIViewController+BaseStyle.h"
#import "NSBundle+BundleForFrameworkModule.h"

@implementation UIViewController (BaseStyle)

- (void)baseStyle_setUpLeftnavigationItem {
    UIButton *leftButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [leftButton setImage:[NSBundle imageName:@"nav_btn_back_n.png" bundleStrForFramework:[self class] module:@"Base"] forState:UIControlStateNormal];
    [leftButton setImage:[NSBundle imageName:@"nav_btn_back_p.png" bundleStrForFramework:[self class] module:@"Base"] forState:UIControlStateHighlighted];
    leftButton.frame = CGRectMake(0, 0, 32, 32);
    [leftButton addTarget:self action:@selector(baseStyle_goBack) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem *leftButtonItem = [[UIBarButtonItem alloc] initWithCustomView:leftButton];
    UIBarButtonItem *spaceItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFixedSpace target:nil action:nil];
    spaceItem.width = -12;
    [self.navigationItem setLeftBarButtonItems:@[spaceItem, leftButtonItem]];
}

- (void)baseStyle_goBack {
    [self.navigationController popViewControllerAnimated:YES];
}
    
@end
