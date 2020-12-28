//
//  Convert.h
//  Pods
//
//  Created by ding_qili on 2019/4/23.
//

#import <Foundation/Foundation.h>


@protocol ConvertDelegate <NSObject>
- (void)onConvertFrame:(NSData *)data Len:(NSInteger)len FrameType:(NSInteger)frameType;
@optional
-(void)convertFinished;
@end

@interface Convert : NSObject

-(BOOL)start:(id<ConvertDelegate>)delegate; //默认dav 后期再扩展
-(void)stop;
-(void)putData:(NSData *)data len:(NSInteger)len;
- (void)startConvertAVIToMP4:(NSString *)srcFile dst:(NSString *)dstFile listener:(id<ConvertDelegate>)delegate;//AVI转码MP4
@end
