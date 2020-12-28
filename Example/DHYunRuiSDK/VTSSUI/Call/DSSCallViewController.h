//
//  DSSCallViewController.h
//  Pods
//
//  Created by 28404 on 2017/11/6.
//

#import <UIKit/UIKit.h>
#import "DSSCallViewModule.h"

@interface DSSCallViewController : UIViewController

@property (nonatomic, strong) DSSCallViewModule *viewModule;

- (void)configNotification:(NSNotification *)notification;

@end
