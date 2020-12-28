//
//  LCOpenSDK_ConvertListener.h
//  LCOpenSDK
//
//  Created by qi sun on 2018/12/28.
//  Copyright © 2018年 Dahua. All rights reserved.
//

#ifndef LCOpenSDK_ConvertListener_h
#define LCOpenSDK_ConvertListener_h

@protocol LCOpenSDK_ConvertListener <NSObject>

/**
 转码进度回调
 
 @param progress 转码进度(百分比)
 */
- (void)onConvertProgress:(NSInteger)progress Index:(NSInteger)index;

/**
 转码错误回调
 
 @param errorCode 错误码(参考OC_CONVERT_ERROR定义)
 */
- (void)onConvertError:(NSInteger)errorCode Index:(NSInteger)index;

/**
 * 转码流数据回调接口
 *
 * @param data [in] 流数据
 * @param len  [in] 流数据长度
 * @param frameType [in] 帧类型 0 for I frame, 1 for P frame, 2 for audio frame
 *
 */
- (void) onConvertFrame:(void*)data Len:(NSInteger)len FrameType:(NSInteger)frameType Index:(NSInteger)index;


@end


#endif /* LCOpenSDK_ConvertListener_h */
