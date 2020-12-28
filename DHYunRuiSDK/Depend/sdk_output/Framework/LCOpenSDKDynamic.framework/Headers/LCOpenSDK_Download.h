//
//  LCOpenSDK_Download.h
//  LCOpenSDK
//
//  Created by baozhiyong on 16/9/5.
//  Copyright © 2016年 lechange. All rights reserved.
//

#import "LCOpenSDK_DownloadListener.h"
#import <Foundation/Foundation.h>

@interface LCOpenSDK_Download : NSObject <LCOpenSDK_DownloadListener>
/**
 *  获取云录像下载组件单例
 *
 *  @return LCOpenSDK_Download单例指针
 */
+ (LCOpenSDK_Download*)shareMyInstance;
/**
 *  设置监听对象
 *
 *  @param listener 监听对象指针
 */
- (void)setListener:(id<LCOpenSDK_DownloadListener>)listener;
/**
 *  获取监听对象指针
 *
 *  @return 监听对象指针
 */
- (id<LCOpenSDK_DownloadListener>)getListener;
/**
 *  开始下载云录像
 *
 *  @param index     下载索引值
 *  @param filepath  下载路径
 *  @param accessTok 管理员token/用户token
 *  @param deviceID  设备ID
 *  @param recordID  录像ID
 *  @param psk       设备密钥
 *  @param type      云录像类型;0:报警 1:定时
 *  @param timeout   接口调用超时时间
 *
 *  @return   0, 接口调用成功
 *           -1, 接口调用失败
 */
- (NSInteger)startDownload:(NSInteger)index filepath:(NSString*)filepath token:(NSString*)accessTok devID:(NSString*)deviceID channelID:(NSInteger)channelID psk:(NSString*)psk recordID:(NSString *)recordID Type:(NSInteger)type Timeout:(NSInteger)timeout;

/**
 *  开始下载设备录像
 *
 *  @param index         下载索引值
 *  @param filepath      下载路径
 *  @param token         管理员token/用户token
 *  @param deviceID      设备ID
 *  @param decryptKey    视频解密密钥
 *  @param fileID        设备录像文件名
 *  @param speed         下载速度：1/2/4/8/16，1表示按正常视频播放速度下载
 *
 *  @return   0, 接口调用成功
 *           -1, 接口调用失败
 */
- (NSInteger)startDownload:(NSInteger)index filepath:(NSString*)filepath token:(NSString*)token devID:(NSString*)deviceID decryptKey:(NSString*)decryptKey fileID:(NSString*)fileID speed:(double)speed;

- (NSInteger)startDownloadWithJsonString:(NSInteger)index jsonString:(NSString*)jsonString;

/**
 *  停止下载云录像
 *
 *  @param index 下载索引值
 *
 *  @return YES, 接口调用成功
 *          NO,  接口调用失败
 */
- (BOOL)stopDownload:(NSInteger)index;

/// 停止全部下载
- (void)stopDownload;

@end
