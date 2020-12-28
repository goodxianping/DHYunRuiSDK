//
//  DSSCallButton.m
//  Pods
//
//  Created by 28404 on 2017/12/5.
//

#import "DSSCallButton.h"

#define IMAGE_WIDTH 62
#define IMAGE_HEIGHT 62

#define IMAGE_TOP 4
#define LABLE_HEIGHT 18
#define LABLE_BOTTOM 2

@interface DSSCallButton()
@property (nonatomic, assign) CGFloat imageHeight;
@property (nonatomic, assign) CGFloat imageWidth;
@end

@implementation DSSCallButton

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    if (self = [super initWithCoder:aDecoder]) {
        self.titleLabel.textAlignment = NSTextAlignmentCenter;
    }
    return self;
}

- (CGRect)titleRectForContentRect:(CGRect)contentRect
{
    return CGRectMake(0, contentRect.size.height - LABLE_HEIGHT - LABLE_BOTTOM, contentRect.size.width, LABLE_HEIGHT);
}

- (CGRect)imageRectForContentRect:(CGRect)contentRect
{
    return CGRectMake((contentRect.size.width - _imageWidth)/2, IMAGE_TOP, _imageWidth, _imageHeight);
}

- (CGRect)contentRectForBounds:(CGRect)bounds
{
    return bounds;
}

#pragma mark --
- (void)setImageWidth:(CGFloat)imageWidth andImageHeight:(CGFloat)imageHeight
{
    _imageWidth = imageWidth;
    _imageHeight = imageHeight;
    [self setNeedsDisplay];
}

@end
