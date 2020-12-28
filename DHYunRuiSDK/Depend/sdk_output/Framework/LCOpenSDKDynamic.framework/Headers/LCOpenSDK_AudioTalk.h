//
//  LCOpenSDK_AudioTalk.h
//  LCOpenSDK
//
//  Created by chenjian on 16/5/16.
//  Copyright (c) 2016年 lechange. All rights reserved.
//

#ifndef LCOpenSDK_LCOpenSDK_AudioTalk_h
#define LCOpenSDK_LCOpenSDK_AudioTalk_h
#import <Foundation/Foundation.h>
#import "LCOpenSDK_TalkerListener.h"
@interface LCOpenSDK_AudioTalk: NSObject
/**
 *  设置监听对象
 *
 *  @param lis 监听对象指针
 */
- (void) setListener:(id<LCOpenSDK_TalkerListener>) lis;
/**
 *  获取监听对象指针
 *
 *  @return 监听对象指针
 */
- (id<LCOpenSDK_TalkerListener>) getListener;
/**
 *  播放语音对讲
 *
 *  @param accessTok 管理员token／用户token
 *  @param deviceID  设备ID
 *  @param psk       设备密钥
 *
 *  @return 接口调用返回值    0, 成功
 *                        －1, 失败
 */
- (NSInteger) playTalk:(NSString*)accessTok devID:(NSString*)deviceID psk:(NSString*)psk;

- (NSInteger) playTalkWithJsonString:(NSString*)jsonString;

/**
 *  停止语音对讲
 *
 *  @return 接口调用返回值    0, 成功
 *                         -1, 失败
 */
- (NSInteger) stopTalk;
- (NSInteger) playSound;
- (NSInteger) stopSound;
- (NSInteger) startSampleAudio;
- (NSInteger) stopSampleAudio;
/**
 判断共享链路的流媒体句柄是否存在

 @param handleKey 共享链路标识
 @return YES：存在；NO：不存在
 */
- (BOOL)isOptHandleOK:(NSString*)handleKey;

/**
 设置音频滤波, 声音降噪

 @param mode -1:不降噪, 0-4:降噪从低到高, 降噪越大对语音损害越大
 */
- (BOOL)setSEnhanceMode:(int)mode;

/**
 获取接收音频回调地址
 */
- (long)getRecvAudioCallBack;

/**
 * 设置对讲是否主动打开扬声器，默认开启
 * @param[in] bEnable TRUE打开，FALSE关闭
 * @return BOOL，成功返回TRUE，失败返回FALSE
 */
+ (BOOL)setSpeakerAutoEnable:(BOOL)bEnable;

/**
 * 设置对讲是否主动打开扬声器，默认开启
 * @param[in] channelId 音频通道号，从0开始
 * @param[in] flag TRUE打开，FALSE关闭
 * @return BOOL，成功返回TRUE，失败返回FALSE
 */
- (BOOL)chooseAudioChannel:(int)channelId flag:(BOOL)bFlag;

/**
 * 获取音频通道数
*/
- (NSInteger)getAudioChannelNum;

@end
#endif
