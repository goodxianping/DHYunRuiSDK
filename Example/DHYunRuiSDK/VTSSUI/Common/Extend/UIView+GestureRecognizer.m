//
//  UIView+GestureRecognizer.m
//  Pods
//
//  Created by xu_weifan on 17/2/18.
//
//

#import "UIView+GestureRecognizer.h"

@implementation UIView (GestureRecognizer)

- (void)addTouchUpInsideWithTarget:(nullable id)target action:(nullable SEL)action {
    self.userInteractionEnabled = YES;
    UITapGestureRecognizer *gestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:target action:action];
    [self addGestureRecognizer:gestureRecognizer];
}

@end
