//
//  LCOpenSDK_PlayWindow.h
//  LCOpenSDK
//
//  Created by chenjian on 16/5/16.
//  Copyright (c) 2016年 lechange. All rights reserved.
//

#ifndef LCOpenSDK_LCOpenSDK_PlayWindow_h
#define LCOpenSDK_LCOpenSDK_PlayWindow_h
#import "LCOpenSDK_EventListener.h"
#import "LCOpenSDK_Define.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

// PS/TS 标准流类型
typedef NS_ENUM(NSInteger, LC_OUTPUT_STREAM_FORMAT)
{
    LC_OUTPUT_STREAM_FORMAT_NULL = 0,   // 不导出流
    LC_OUTPUT_STREAM_FORMAT_PS,         // PS标准流
    LC_OUTPUT_STREAM_FORMAT_TS          // TS标准流
};

@interface FisheyeCorrdinate : NSObject
@property (nonatomic) NSInteger FisheyeCoordinate_X; /* 点链坐标X */
@property (nonatomic) NSInteger FisheyeCoordinate_Y; /* 点链坐标Y */
@end

@interface FisheyeSubWinInfo : NSObject
@property (nonatomic) NSInteger SubWinNum;   /* 子窗口序号 */
@property (nonatomic) NSInteger SubWin_Corrdinate_X; /* 子窗口横坐标X */
@property (nonatomic) NSInteger SubWin_Corrdinate_Y;  /* 子窗口纵坐标 */
@property (nonatomic) NSInteger SubWin_W;    /* 子窗口宽度 */
@property (nonatomic) NSInteger SubWin_H;    /* 子窗口高度 */
@end

@interface LCOpenSDK_PlayWindow : NSObject <LCOpenSDK_EventListener>

/**
 *  初始化播放窗口
 *
 *  @param frame 窗口
 *  @param index 播放窗口索引
 *
 *  @return LCOpenSDK_PlayWindow指针
 */
- (id)initPlayWindow:(CGRect)frame Index:(NSInteger)index;
/**
 *  反初始化播放窗口
 */
- (void)uninitPlayWindow;
/**
 *  设置播放窗口手势操作事件是否被上层窗口捕获
 *
 *  @param flag 布尔值
 */
- (void)openTouchListener:(BOOL)flag;
/**
 *  获取索引值
 *
 */
- (NSInteger)getIndex;
/**
 *  设置索引值
 * @param index 索引值，播放前传入，回调时带出，用于上层在使用同一监听对象时区分不同播放对象的回调
 */
- (void)setIndex:(NSInteger)index;
/**
 *  获取播放窗口
 *
 *  @return 播放窗口指针
 */
- (UIView*)getWindowView;
/**
 *  设置播放窗口
 *
 *  @param rect 播放窗口
 */
- (void)setWindowFrame:(CGRect)rect;
/**
 *  设置播放窗口监听对象
 *
 *  @param lis 监听对象指针
 */
- (void)setWindowListener:(id<LCOpenSDK_EventListener>)lis;
/**
 *  获取播放窗口监听对象指针
 *
 *  @return 监听对象指针
 */
- (id<LCOpenSDK_EventListener>)getWindowListener;
/**
 *  设置播放窗口背景色
 *
 *  @param normalColor 背景色
 */
- (void)setSurfaceBGColor:(UIColor*)normalColor;
/**
 *  播放实时视频
 *
 *  @param accessTok 管理员token/用户token
 *  @param deviceID  设备ID
 *  @param psk       设备密钥
 *  @param chn       通道ID
 *  @param defiMode  流媒体HD/SD模式
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger) playRtspReal:(NSString*)accessTok devID:(NSString*)deviceID psk:(NSString*)psk channel:(NSInteger)chn definition:(NSInteger)defiMode;
/**
 *  停止实时视频播放
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)stopRtspReal;

/**
 *  开始设备录像回放
 *
 *  @param accessTok 管理员token／用户token
 *  @param deviceID  设备ID
 *  @param psk       设备密钥
 *  @param chn       通道ID
 *  @param fileName  设备本地录像文件名
 *  @param beginTime 本地录像开始播放时间
 *  @param endTime   本地录像结束播放时间
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger) playDeviceRecord:(NSString*)accessTok devID:(NSString*)deviceID psk:(NSString*)psk channel:(NSInteger)chn fileName:(NSString*)fileName begin:(long)beginTime end:(long)endTime offsetTime:(double)offsetTime;

- (NSInteger) playDeviceRecordByFileName:(NSString*)accessTok devID:(NSString*)deviceID psk:(NSString*)psk fileName:(NSString*)fileName offsetTime:(double)offsetTime;

- (NSInteger) playDeviceRecordByUtcTime:(NSString*)accessTok devID:(NSString*)deviceID psk:(NSString*)psk channel:(NSInteger)chn begin:(long)beginTime end:(long)endTime;

/**
 *  停止设备录像回放
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)stopDeviceRecord;

/**
 *  播放云录像(可设置接口调用超时时长)
 *
 *  @param accessTok 管理员token/用户token
 *  @param deviceID  设备ID
 *  @param channelID 设备通道号
 *  @param psk       设备密钥
 *  @param recordID  录像ID
 *  @param type      云录像类型;0:报警 1:定时
 *  @param timeOut   超时时长
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)playCloud:(NSString*)accessTok devID:(NSString*)deviceID channelID:(NSInteger)channelID psk:(NSString*)psk recordID:(NSString*)recordID offsetTime:(NSInteger)offsetTime Type:(NSInteger)type timeOut:(NSInteger)timeOut;
/**
 *  停止云录像播放
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)stopCloud;
/**
 *  播放音频
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)playAudio;
/**
 *  停止音频
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)stopAudio;
/**
 *  录像拖动
 *
 *  @param timeInfo 相对开始时间偏移的秒数
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)seek:(NSInteger)timeInfo;
/**
 *  暂停播放
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)pause;
/**
 *  恢复播放
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)resume;
/**
 *  截图
 *
 *  @param filePath 图片保存路径
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)snapShot:(NSString*)filePath;
/**
 *  开始录制视频
 *
 *  @param filePath    录制视频保存路径
 *  @param nRecordType 录制视频格式: 0, dav
 *                                 1, mp4
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)startRecord:(NSString*)filePath recordType:(NSInteger)nRecordType;
/**
 *  停止录制视频
 *
 *  @return 0, 接口调用成功
 *         -1, 接口调用失败
 */
- (NSInteger)stopRecord;
/**
 *  设置PS/TS标准流导出
 *
 *  @param streamFormat [in] 标准流类型
 */
- (void)setStreamCallback:(LC_OUTPUT_STREAM_FORMAT)streamFormat;
/**
 *  EPTZ缩放操作
 *
 *  @param scale 缩放比例
 */
- (void)doScale:(CGFloat)scale;
/**
 *  获取EPTZ缩放比例
 *
 *  @return －1, 失败
 *         其他, 成功
 */
- (CGFloat)getScale;
/**
 *  窗口平移开始
 *
 *  @return YES, 成功
 *          NO, 失败
 */
- (BOOL)doTranslateBegin;
/**
 *  EPTZ滑动操作
 *
 *  @param x 播放窗口X坐标值
 *  @param y 播放窗口Y坐标值
 */
- (void)doTranslateX:(CGFloat)x Y:(CGFloat)y;
/**
 *  窗口平移结束
 *
 *  @return YES, 成功
 *          NO, 失败
 */
- (BOOL)doTranslateEnd;
/**
 *  获取当前平移的X轴位置（百分比）
 *
 *  @return 位置（-100%-100%）
 */
- (CGFloat)getTranslatePercentX;
/**
 *  获取当前平移的Y轴位置（百分比）
 *
 *  @return 位置（-100%-100%）
 */
- (CGFloat)getTranslatePercentY;
/**
 *  获取窗口移动距离（X坐标）
 *
 *  @return 移动距离
 */
- (CGFloat)getTranslateX;
/**
 *  获取窗口移动距离（Y坐标）
 *
 *  @return 移动距离
 */
- (CGFloat)getTranslateY;
/**
 *  电子缩放开始
 *
 *  @return 无
 */
- (void)doEZoomBegin;
/**
 *  电子缩放
 *  @param 倍数
 *  @return 无
 */
- (void)doEZooming:(CGFloat)scale;
/**
 *  电子缩放结束
 *  @return 无
 */
- (void)doEZoomEnd;
/**
 *  重置画面缩放平移操作
 *  @return 无
 */
- (void)setIdentity;
/**
 *  获取当前拉流类型
 *  @return 当前拉流类型（参考E_STREAM_MODE定义）
 */
- (E_STREAM_MODE)getCurrentStreamMode;
/**
 *  按照JSON串格式播放
 *  @param  jsonString json参数串
 *  @return 0/非0 调用成功／调用失败
 */
-(NSInteger)playBrotherWithJsonString:(NSInteger)baseIndex jsonParam:(NSString*)jsonString;

-(NSInteger)stopBrotherPlay;

-(BOOL)switcherPlayer:(BOOL)isStopFront bg:(BOOL)isOpenBg;
/**
 *  按照JSON串格式播放
 *  @param  jsonString json参数串
 *  @return 0/非0 调用成功／调用失败
 */
-(NSInteger)playWithJsonString:(NSString*)jsonString;
/**
 *  停止播放
 *  @return 0/非0 调用成功／调用失败
 */
-(NSInteger)stopPlay;

/**
 停止播放, 保留最后一帧

 @param isKeepLastFrame 是否保留最后一帧
 @return 结果
 */
- (NSInteger)stopPlay:(BOOL)isKeepLastFrame;
/**
 *  设置最大缩放比例
 *  @param scale  最大缩放倍数
 *  @return
 */
-(void)setMaxScale:(CGFloat)scale;
/**
 *  是否需要通过决策服务获取走P2P策略
 *  @param yesOrNo  BOOL
 *  @return
 */
//-(void)isUseReportSvr:(BOOL)yesOrNo;
/**
 *  设置播放速度，正常播放速度是1.0
 *  @param speed 播放倍速
 *  @return
 */
-(void)setPlaySpeed:(float)speed;
/**
 *  获取当前播放速度
 *  @return 播放速度
 */
-(float)getPlaySpeed;
/**
 *  使能鱼眼
 *  @return YES/NO 成功／失败
 */
-(BOOL)enableFishEye;
/**
 *  禁用鱼眼
 *  @return
 */
-(void)disableFishEye;
/**
 *  开始鱼眼操作
 *  @param x,y
 *  @return YES/NO
 */
-(BOOL)startFishEye:(float)x y:(float)y;
/**
 *  操作鱼眼
 *  @param x,y
 *  @return
 */
-(void)doingFishEye:(float)x y:(float)y;
/**
 *  结束鱼眼操作
 *  @return YES/NO
 */
-(BOOL)endFishEye;
/**
 *  设置去噪模式等级（playsound之后调用生效）
 *  @param mode(-1,0,1,2,3,4)
 * -1 不进行噪声消除 0 噪声消除程度最低，对有用语音信号的损害最小
 * 4 噪声消除程度最大，对有用语音信号的损害最大
 *  @return YES/NO
 */
-(BOOL)setSEnHanceMode:(NSInteger)mode;
/**
 *  播放下一帧
 *  @return
 */
-(void)playNextFrame;
/**
 *  播放连续帧
 *  @return
 */
-(void)playContinuousFrame;

/**
 是否为录制状态
 */
- (BOOL) isRecording;

/**
 获取播放状态
 STATUS_PLAYING      0
 STATUS_STOPED       1
 STATUS_PAUSE        2
 STATUS_REQUESING    3
 STATUS_FAILED       4
 STATUS_SEEKING      5
 */
- (NSInteger) getPlayerStatus;

/**
 * 鱼眼设置安装模式校正模式
 * @param [in] installMode安装模式
 * @param [in] correctMode校正模式
 *
 * @return 设置安装模式和矫正模式是否成功
 * - false：失败
 * - true：成功
 *
 * @see 设置成功后淮安会依照校正模式变成鱼眼画面
 */
- (BOOL )fishEyeSetOptInfo:(NSInteger)installMode
               correctMode:(NSInteger)correctMode;

/**
 * 鱼眼获取画线信息
 * @param [in] winType 窗口类型：0鱼眼圆，1全景，2子窗口
 * @param [in] winId 窗口序号：从0开始，从左至右， 从上至下
 * @param [in] screenResolutionH：想要得到的屏幕输出分辨率H
 * @param [in] screenResolutionW: 想要得到的屏幕输出分辨率W
 * @param [out] pFishEyeCoordinate: 鱼眼点链坐标，用于在鱼眼圆上或者全景上绘制畸变线
 * @param [out] pSubWinCoordinate: 子窗口坐标，用于绘制子窗口边框
 *
 * @return 获取坐标是否成功
 * - false: 失败
 * - true: 成功
 */
- (BOOL )fishEyeGetOptInfo:(NSInteger)winType
                     winId:(NSInteger)winId
         screenResolutionH:(NSInteger)screenResolutionH
         screenResolutionW:(NSInteger)screenResolutionW
        pFishEyeCoordinate:(NSMutableArray<FisheyeCorrdinate*>*)pFishEyeCoordinate
         pSubWinCoordinate:(NSMutableArray<FisheyeSubWinInfo*>*)pSubWinCoordinate;

/**
 * 鱼眼检查指定点是否在子窗口内
 * @param [in] winId 指定窗口的窗口序号：从0开始，从左至右， 从上至下
 * @param [in] pointX 指定点的横坐标
 * @param [in] pointY 指定点的纵坐标
 *
 * @return 点是否在指定子窗口内
 * - false: 不在指定子窗口内
 * - true：在指定子窗口内
 */
- (BOOL )fishEyeCheckPointPosition:(NSInteger)winId
                            pointX:(NSInteger)pointX
                            pointY:(NSInteger)pointY;

/**
 * 鱼眼拖动画面功能
 * @param [in] winType 窗口类型：0鱼眼圆，1全景，2子窗口
 * @param [in] winId 指定窗口的窗口序号：从0开始，从左至右， 从上至下
 * @param [in] OffsetX 拖拽的横向偏移长度
 * @param [in] OffsetY 拖拽的纵向便宜长度
 * @param [out] pFishEyeCoordinate: 鱼眼点链坐标，用于在鱼眼圆上或者全景上绘制畸变线
 *
 * @return 拖拽是否成功
 * - flase：拖拽失败
 * - true：拖拽成功
 */
- (BOOL )fishEyeDragPic:(NSInteger)winType
                  winId:(NSInteger)winId
                OffsetX:(NSInteger)OffsetX
                OffsetY:(NSInteger)OffsetY
     pFishEyeCoordinate:(NSMutableArray<FisheyeCorrdinate*>*)pFishEyeCoordinate;

/**
 * 鱼眼移动功能
 * @param [in] moveDirection 0左移 1右移 2上移 3下移
 * @param [in] moveRange  壁装全景移动1~180*128  地装顶装全景移动范围1~360*128 (移动方向需要和安装模式对应)
 * @param [in] winId 指定窗口的窗口序号：从0开始，从左至右， 从上至下
 * @param [out] pFishEyeCoordinate: 鱼眼点链坐标，用于在鱼眼圆上或者全景上绘制畸变线
 *
 * @return 操作是否成功
 * - flase：操作失败
 * - true：操作成功
 */
-(BOOL) fishEyeMove:(int)moveDirection
          moveRange:(int)moveRange
              winId:(int)winId
 pFishEyeCoordinate:(NSMutableArray<FisheyeCorrdinate*>*)pFishEyeCoordinate;

/**
 * 鱼眼放大缩小功能
 * @param [in] operateMode 0放大 1缩小
 * @param [in] multiple  放大缩小倍数1~8
 * @param [in] winId 指定窗口的窗口序号：从0开始，从左至右， 从上至下
 * @param [out] pFishEyeCoordinate: 鱼眼点链坐标，用于在鱼眼圆上或者全景上绘制畸变线
 *
 * @return 操作是否成功
 * - flase：操作失败
 * - true：操作成功
 */
-(BOOL) fishEyeExtend:(int)operateMode
             multiple:(int)multiple
                winId:(int)winId
   pFishEyeCoordinate:(NSMutableArray<FisheyeCorrdinate*>*)pFishEyeCoordinate;


/**
 * 鱼眼圆旋转功能
 * @param [in] direction  圆旋转范围(仅限于操作的窗口为鱼眼圆或者手机模式) 顺时针：1~360*128，逆时针： -360*128~-1
 * @param [in] winId 指定窗口的窗口序号：从0开始，从左至右， 从上至下
 * @param [out] pFishEyeCoordinate: 鱼眼点链坐标，用于在鱼眼圆上或者全景上绘制畸变线
 *
 * @return 操作是否成功
 * - flase：操作失败
 * - true：操作成功
 */
-(BOOL) fishEyeRotate:(int)direction
                winId:(int)winId
   pFishEyeCoordinate:(NSMutableArray<FisheyeCorrdinate*>*)pFishEyeCoordinate;

/**
 * 设置PLAYSDK log等级
 * 0,  unknown
 * 1,  fatal, when setting this level, (fatal) will output
 * 2,  error,when setting this level, (fatal,error) will output
 * 3,  warn, when setting this level, (fatal,error,warn) will output
 * 4,  info, when setting this level, (fatal,error,warn,info) will output
 * 5,  Trace, when setting this level, (fatal,error,warn,info,trace) will output
 * 6,  Debug, when setting this level, (fatal,error,warn,info,trace,debug) will output
 */
- (void)setPlaySDKLog:(int)level;

/**
 * 设置GDPR加密密钥
 */
- (void )setKey:(NSString*)passwordkey;

/**
 * 设置解码： 0软解， 1硬解
 */
- (void)setDecodeEngine:(NSInteger)engineType;

/**
 *设置网络自适应策略
 */
- (void)setRealPlayPolicy:(NSInteger)realPlayType playPolicy:(NSInteger)playPolicy waitTime:(NSInteger)waitTime;

- (NSNumber*)getPlayHandle;
- (NSNumber*)getLoginHandle;
/**
 判断共享链路的流媒体句柄是否存在

 @param handleKey 共享链路标识
 @return YES：存在；NO：不存在
 */
- (BOOL)isOptHandleOK:(NSString*)handleKey;

/**
 * 设置或增加显示区域， 可以做局部放大显示
 * @param regionNum 显示区域序号，0~(MAX——DISPLAY_WND-1), 0为将设置的区域显示在主窗口中 
 * @param view 显示窗口句柄
 * @param bEnable 打开或关闭显示区域
 */
- (BOOL)setDisPlayRegion:(int)regionNum view:(void*)view bEnable:(BOOL)bEnable;

/**
 * 判断是否是鱼眼码流
 */
- (BOOL)isFishEyeStream;

/// 设置播放窗口k宽高比
/// @param width 宽
/// @param height 高
- (BOOL)setViewProportionWidth:(int)width height:(int)height;

/**
* 设置视频伴音音频通道开关
* @param [in]channelId 音频通道号，从0开始
* @param [in]flag YES打开，NO关闭
*
* @return BOOL 成功返回TRUE，失败返回FALSE
*/
- (BOOL)chooseAudio:(NSInteger)channelId flag:(BOOL)flag;

/**
 * 获取视频伴音的音频通道总数, 此接口只有在有解析码流后才有效 
 * @return 音频通道总数 ，返回-1时为调用失败
 */
- (NSInteger)getAudioChannelNum;

/**
 * 按文件片回放补充文件片
 * @param fileListJson 文件片信息的json串
 * @return -1失败, 0成功
 */
- (NSInteger)addFileList:(NSString*)fileListJson;

@end

#endif
