//
//  UIView+GestureRecognizer.h
//  Pods
//
//  Created by xu_weifan on 17/2/18.
//
//

#import <UIKit/UIKit.h>

@interface UIView (GestureRecognizer)

/**
 * 普通视图添加点击事件
 */
- (void)addTouchUpInsideWithTarget:(nullable id)target action:(nullable SEL)action;

@end
