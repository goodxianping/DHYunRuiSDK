//
//  LCSDK_Define.h
//  LCSDK
//
//  Created by zhou_yuepeng on 16/12/2.
//  Copyright © 2016年 com.lechange.lcsdk. All rights reserved.
//

#ifndef __LCSDK_LCSDK_DEFINE_H__
#define __LCSDK_LCSDK_DEFINE_H__

#import <Foundation/Foundation.h>

#pragma mark - 码流类型
typedef NS_ENUM(NSInteger, E_STREAM_TYPE)
{
    STREAM_MAIN,        //主码流
    STREAM_MINOR_1,     //辅码流1
    STREAM_MINOR_2,     //辅码流2
    STREAM_MINOR_3,     //辅码流3
};
#pragma mark - 音频编码类型
typedef NS_ENUM(NSInteger, E_AUDIO_ENCODE_TYPE)
{
    AUDIO_ENCODE_PCM8   = 7,
    AUDIO_ENCODE_G711A  = 14,
    AUDIO_ENCODE_PCM16  = 16,
    AUDIO_ENCODE_G711U  = 22
};
#pragma mark - 录像来源类型
typedef NS_ENUM(NSInteger, E_RECSOURCE_TYPE)
{
    RECSOURCE_TYPE_ALL = 1,     //所有
    RECSOURCE_TYPE_DEVICE,      //设备录像
    RECSOURCE_TYPE_PLATFORM,    //平台录像
};
#pragma mark - HLS类型
typedef NS_ENUM(NSInteger, E_HLS_TYPE)
{
    PLAYBACK_DH_HLS = 0,    //回放-大华HLS
    PLAYBACK_STANDARD_HLS,  //回放-标准HLS
    LIVE_DH_HLS,            //直播-大华HLS
    LIVE_STANDARD_HLS,      //直播-标准HLS
    PLAYBACK_AMAZON_HLS,    //回放-amazon s3 HLS
    PLAYBACK_SAAS_HLS,      //回放-SAAS HLS
};

#pragma mark - 切片地址前缀类型
typedef NS_ENUM(NSInteger, E_SLICE_PREFIX_TYPE)
{
    SLICE_PREFIX_WITH_HOST, //以rest host为切片前缀
    SLICE_PREFIX_FROM_URL,  //从m3u8地址中截取切片前缀
};

#pragma mark - 视频格式
typedef NS_ENUM(NSInteger, E_MEDIA_FORMAT)
{
    MEDIA_DAV,          //DAV格式
    MEDIA_MP4,          //MP4格式
};

#pragma mark - 云存储录像类型
typedef NS_ENUM(NSInteger, E_CLOUD_RECORD_TYPE)
{
    CLOUD_RECORD_MANUAL     = 1,        //手动录像(X-MINI设备功能)
    CLOUD_RECORD_LEAVE_MSG  = 2,        //留言(TC5S需求)
    CLOUD_RECORD_ASK_HELP   = 3,        //求救录像(TC5S需求>已废弃)
    CLOUD_RECORD_ALARM      = 1000,     //告警录像(原报警录像)
    CLOUD_RECORD_HEAD_CHECK = 1001,     //人头检测录像(TC5S需求)
    CLOUD_RECORD_TIMING     = 2000,     //定时录像
    E_CLOUD_RECORD_DATE     = 5001,     //聚合录像（快放一整天需求）
};

#pragma mark - 拉流类型
typedef NS_ENUM(NSInteger, E_STREAM_MODE)
{
    STREAM_MODE_UNCERTAINTY = -1,    //拉流方式未确定(指当前没有在拉流or在拉流准备中or不涉及下面两种类型)
    STREAM_MODE_P2P,                 //使用P2P拉流
    STREAM_MODE_MTS,                 //使用MTS拉流
};

#pragma mark - 视频转换类型
typedef NS_ENUM(NSInteger, E_MEDIA_CONVERT_TYPE)
{
    MEDIA_CONVERT_DAV,
    MEDIA_CONVERT_MP4,
    MEDIA_CONVERT_AVI,
    MEDIA_CONVERT_ASF,
    MEDIA_CONVERT_FLV,
    MEDIA_CONVERT_MOV,
    MEDIA_CONVERT_MP464,
    MEDIA_CONVERT_MOV64,
    MEDIA_CONVERT_MP4NOSEEK,
    MEDIA_CONVERT_WAV,
    MEDIA_CONVERT_TS,
    MEDIA_CONVERT_PS,
};

#pragma mark - 获取登录句柄失败错误码
typedef NS_ENUM(NSInteger, E_LOGIN_ERROR_CODE)
{
    LOGIN_ERROR_P2P_FAILED                     = 100, //p2p打洞失败
    LOGIN_ERROR_UNSUPPORT_HIGH_SECURITY        = 199, //设备不支持高安全等级登录
    LOGIN_ERROR_NONE                           = 200, //无错误
    LOGIN_ERROR_KEY_MISMATCH                   = 201, //密码不正确
    LOGIN_ERROR_USER_NOTEXIST                  = 202, //账户不存在
    LOGIN_ERROR_TIMEOUT                        = 203, //连接超时
    LOGIN_ERROR_LOGIN_REPEAT                   = 204, //重复登录
    LOGIN_ERROR_USER_LOCKED                    = 205, //账户被锁定
    LOGIN_ERROR_USER_BLACKLIST                 = 206, //账户被加入黑名单
    LOGIN_ERROR_SYSTEM_BUSY                    = 207, //系统繁忙(资源不足)
    LOGIN_ERROR_SUBCONNECT_FAILED              = 208, //子连接失败
    LOGIN_ERROR_MAINCONNECT_FAILED             = 209, //主连接失败
    LOGIN_ERROR_OVER_MAX_CONNECT               = 210, //超出最大连接数
    LOGIN_ERROR_ONLY_SUPPORT_THREE_PROTOCOL    = 211, //只支持三代协议
    LOGIN_ERROR_NO_USB_KEY                     = 212, //没有插入U盾
    LOGIN_ERROR_IP_UNAUTHORIZED                = 213, //客户端IP地址没有登录权限
    LOGIN_ERROR_KEY_MISMATCH_OR_USER_NOTEXIST  = 217, //密码不正确或者账户不存在(老设备使用)
    LOGIN_ERROR_USER_NOT_INITIALIZED           = 218, //设备账号未初始化，无法登陆
    LOGIN_ERROR_LOGIN_LIMITED                  = 219, //登录受限
    LOGIN_ERROR_ONLY_SUPPORT_HIGH_SECURITY     = 220, //设备只支持高安全级别登陆
};

#pragma mark - 设备状态
typedef NS_ENUM(NSInteger, E_DEVICE_STATE)
{
    DEVICE_STATE_ON_LINE = 0,       //在线
    DEVICE_STATE_OFF_LINE = 1,      //离线
    DEVICE_STATE_UNKNOWN,           //未知
};
#pragma mark - 加密结果
typedef NS_ENUM(NSInteger, E_ENCRYPT_RESULT)
{
    ENC_Success = 0,          //encrypt success
    ENC_NotWhole,             //not a whole frame
    ENC_Encrypted,            //already encrypted
    ENC_BufNotEnough,         //buf not enough
    ENC_InternalError = 99,   //internal error
};

#pragma mark - 解密结果
typedef NS_ENUM(NSInteger, E_DECRYPT_RESULT)
{
    Dec_Success = 0,          //decrypt success
    Dec_NotWhole,             //dada not whole
    Dec_KeyError,             //decrypt key error
    Dec_UnEncrypt,            //unencrypt
    Dec_UnsupportEncryption,  //unsupport encryption
    Dec_BufNotEnough,         //buf not enough
    Dec_InternalError = 99,   //internal error
};

#pragma mark - 秘钥计算规则版本
typedef NS_ENUM(NSInteger, E_RULE_VERSION)
{
    RULE_EASY4IP = 0,       //Base64(MD5_LOWER("HS:"+MD5_LOWER(keyseed))+"EASY4IP"), 取前16位
    RULE_LECHANGE,          //Base64(MD5_LOWER("HS:"+MD5_LOWER(keyseed))), 取前16位
    RULE_DAHUAPASS,         //Base64(MD5_UPPER("HS:"+MD5_UPPER(keyseed))), 取前16位
};

#pragma mark -  onPlayerResult回调type参数定义
typedef NS_ENUM(NSUInteger, OC_PROTO_TYPE)
{
    OC_RESULT_PROTO_TYPE_RTSP,      //RTSP业务(包括实时预览、本地录像回放、对讲)
    OC_RESULT_PROTO_TYPE_HLS,       //HLS业务(包括云录像播放、云录像下载)
    OC_RESULT_PROTO_TYPE_FILE,      //FILE业务(包括本地文件播放)
    OC_RESULT_PROTO_TYPE_NETSDK,    //NETSDK业务(包括大华P2P设备实时预览、录像回放)
    OC_RESULT_PROTO_TYPE_SIP,       //SIP业务(包括大华Meeting)
    OC_RESULT_PROTO_TYPE_DHHTTP,    //HTTP优化拉流业务(包括大华Meeting)
    OC_RESULT_PROTO_TYPE_DPSDK,     //
    OC_RESULT_PROTO_TYPE_Express,   //
    OC_RESULT_PROTO_TYPE_CloudBase, //
    OC_RESULT_PROTO_TYPE_RTP,       //
    OC_RESULT_PROTO_TYPE_FINANCECLOUD,      //招行金融云
    OC_RESULT_PROTO_TYPE_COMMUNITYCLOUD,    //社区云
    OC_RESULT_PROTO_TYPE_REST = 99, //REST业务(涉及以上RTSP、HLS、SIP业务)
    
    OC_RESULT_PROTO_TYPE_TALK_RESPONSE_SESSIONID       = 34712, //AudioSession
    OC_RESULT_PROTO_TYPE_TALK_RESPONSE_PORT            = 34713, //AudioPort
    OC_RESULT_PROTO_TYPE_TALK_RESPONSE_SESSIONID_VIDEO = 34714, //VideoSession
    OC_RESULT_PROTO_TYPE_TALK_RESPONSE_PORT_VIDEO      = 34715, //VideoPort
};

#pragma mark -  when type == RESULT_PROTO_TYPE_RTSP, code enum
typedef NS_ENUM(NSInteger, OC_RTSP_STATE)
{
    OC_STATE_PACKET_COMPONENT_ERROR = -1, //组件内部调用流媒体接口失败
    OC_STATE_PACKET_FRAME_ERROR = 0,     //组帧失败
    OC_STATE_RTSP_TEARDOWN_ERROR,        //内部要求关闭,如连接断开等
    OC_STATE_RTSP_DESCRIBE_READY,        //会话已经收到Describe响应
    OC_STATE_RTSP_AUTHORIZATION_FAIL,    //RTSP鉴权失败
    OC_STATE_RTSP_PLAY_READY,            //收到PLAY响应
    OC_STATE_RTSP_FILE_PLAY_OVER,        //录像文件回放正常结束
    OC_STATE_RTSP_PAUSE_READY,           //收到PAUSE响应
    OC_STATE_RTSP_KEY_MISMATCH,          //密钥不正确
	OC_STATE_RTSP_LIVE_PAUSE_ENABLE,     //服务端直播支持PAUSE , 调用stream_inquirePause接口后会收到该消息或者STATE_RTSP_LIVE_PAUSE_DISABLE 消息
    OC_STATE_RTSP_LIVE_PAUSE_DISABLE,    //服务端直播不支持PAUSE
    OC_STATE_RTSP_TALK_BUSY_LINE,        //对讲忙线
    OC_STATE_RTSP_TALK_CHECK_FAILED,     //对讲不满足操作条件
    OC_STATE_RTSP_SERVICE_UNAVAILABLE =  99,  // 基于503 错误码的连接最大数错误
    OC_STATE_RTSP_USER_INFO_BASE_START = 100, // 用户信息起始码, 服务端上层传过来的信息码会在该起始码基础上累加
    OC_STATE_RTSP_STREAM_LIMIT_NOTIFY = 101,         //流量限制通知
    OC_STATE_RTSP_CONCURRENT_LIMIT_NOTIFY = 102,     //并发限制通知
};

#pragma mark -  when type == OC_RESULT_PROTO_TYPE_DHHTTP, code enum
typedef NS_ENUM(NSInteger, OC_DHHTTP_STATE)
{
    OC_STATE_DHHTTP_COMPONENT_ERROR = -1,           //组件内部调用流媒体接口失败
    OC_STATE_DHHTTP_OK = 1000,                      //开启播放成功
    OC_STATE_DHHTTP_PLAY_FILE_OVER = 2000,          //回放时，当前文件播放完毕
    OC_STATE_DHHTTP_BAD_REQUEST = 400000,           //非法请求，关闭客户端
    OC_STATE_DHHTTP_UNAUTHORIZED = 401000,          //未授权，用户名密码错误
    OC_STATE_DHHTTP_FORBIDDEN = 403000,             //禁止访问，关闭客户端
    OC_STATE_DHHTTP_NOTFOUND = 404000,             //未找到，关闭客户端
    OC_STATE_DHHTTP_REQ_TIMEOUT = 408000,          //请求超时，指拉流成功，但后续网络异常，导致拉流断开
    OC_STATE_DHHTTP_SERVER_ERROR = 500000,          //服务器内部错误，关闭客户端
    OC_STATE_DHHTTP_SERVER_UNVALILABLE = 503000,    //服务不可用
    OC_STATE_DHHTTP_FLOWLIMIT      = 503006,        //mts限流
    OC_STATE_DHHTTP_P2P_MAXCONNECT = 503007,        //p2p达到最大链接数
    OC_STATE_DHHTTP_GATEWAY_TIMEOUT    = 504000,    //网络不通
    OC_STATE_DHHTTP_CLIENT_ERROR       = 1000000,   //客户端内部错误，一般代码逻辑错误
    OC_STATE_DHHTTP_KEY_ERROR          = 1000005,   //客户端密钥和服务端密钥不一致
};

#pragma mark -  when type == OC_RESULT_PROTO_TYPE_HLS, code enum
typedef NS_ENUM(NSInteger, OC_HLS_STATE)
{
    OC_STATE_HLS_DOWNLOAD_FAILD,        //下载失败
    OC_STATE_HLS_DOWNLOAD_BEGIN,        //开始下载
    OC_STATE_HLS_DOWNLOAD_END,          //下载结束
    OC_STATE_HLS_SEEK_SUCCESS,          //定位成功
    OC_STATE_HLS_SEEK_FAILD,            //定位失败
    OC_STATE_HLS_ABORT_DONE,
    OC_STATE_HLS_RESUME_DONE,
    OC_STATE_HLS_KEY_MISMATCH = 11,     //密钥不正确
	OC_STATE_HLS_EXTRACT_FAILED = 13,   //抽帧失败需要app设置播放速度为1 
};

#pragma mark -  when type == OC_RESULT_PROTO_TYPE_SIP, code enum
typedef NS_ENUM(NSInteger, OC_SIP_STATE)
{
    OC_STATE_SIP_PLAY_FAILD = -1,       //大华Meeting失败
};

#pragma mark -  when type == OC_RESULT_PROTO_TYPE_NETSDK, code enum
typedef NS_ENUM(NSInteger, OC_NETSDK_STATE)
{
    OC_STATE_NETSDK_FAILD = -1,    //大华P2P设备播放或对讲失败
    OC_STATE_NETSDK_SUCCESS = 0,   //大华P2P设备播放或对讲成功
};

#pragma mark -  when type == OC_RESULT_PROTO_TYPE_REST, code enum
typedef NS_ENUM(NSInteger, OC_REST_STATE)
{
    OC_STATE_REST_CONNECTION_FAILD = -1, //REST连接超时
};

#pragma mark -  when type == OC_RESULT_PROTO_TYPE_FILE, code enum
typedef NS_ENUM(NSInteger, OC_FILE_STATE)
{
    OC_STATE_FILE_INIT_FAILD = -1, //本地文件播放初始化失败
    OC_STATE_FILE_PLAY_SEEK_FAILED = 6,         // 拖拽失败
    OC_STATE_FILE_PLAY_SEEK_SUCCESS = 7,         // 拖拽成功
    OC_STATE_FILE_PLAY_CROSS_BORDER = 8,        // 拖拽越界
};

#pragma mark - when media convert, error code enum
typedef NS_ENUM(NSInteger, OC_CONVERT_ERROR)
{
    OC_CONVERT_ERROR_INVALID_HANDLE,        //无效句柄
    OC_CONVERT_ERROR_UNSUPPORT,             //解析或封装类型不支持
    OC_CONVERT_ERROR_THREAD,                //内部线程出错
    OC_CONVERT_ERROR_PARAM,                 //参数有误
    OC_CONVERT_ERROR_FILE_OPEN,             //文件打开出错，可能已被互斥打开
    OC_CONVERT_ERROR_FILE_READ,             //文件读取出错
    OC_CONVERT_ERROR_FILE_WRITE,            //文件写入出错
    OC_CONVERT_ERROR_FORMAT,                //格式有误，无法继续解析
    OC_CONVERT_ERROR_BUFFER_OVER_FLOW,      //内部缓冲溢出
    OC_CONVERT_ERROR_SYSOUTOFMEM,           //系统内存不足
    OC_CONVERT_ERROR_NO_IDR_FRAME,          //缺少I帧
    OC_CONVERT_ERROR_NO_OUTPUT,             //同步封装或解析逻辑中无数据输出
    OC_CONVERT_ERROR_ORDER,                 //调用顺序有误
    OC_CONVERT_ERROR_ENCRYPT_KEY,           //秘钥错误
};

#pragma mark -  when type == OC_LOGIN_STATE, code enum
typedef NS_ENUM(NSInteger, OC_LOGIN_STATE)
{
    OC_LOGIN_STATE_INIT = 1,                //初始化
    OC_LOGIN_STATE_P2P_SUCCESS,          //预打洞成功
    OC_LOGIN_STATE_P2P_FAILED,           //预打洞失败
    OC_LOGIN_STATE_LOGIN_SUCCESS,           //登陆成功
    OC_LOGIN_STATE_LOGIN_FAILED,            //登陆失败
};

#pragma mark - 对讲状态回调 when type == OC_RESULT_PROTO_TYPE_DPSDK || OC_RESULT_PROTO_TYPE_Express || OC_RESULT_PROTO_TYPE_CloudBase, code enum
typedef NS_ENUM(NSInteger, OC_INDUSTRYPLTM_TALK_STATE)
{
    OC_STATE_INDUSTRYPLTM_START_TALK_SUCCESS = 1,   //打开对讲成功
    OC_STATE_INDUSTRYPLTM_START_TALK_FAILED,        //打开对讲失败
    OC_STATE_INDUSTRYPLTM_RESTART_TALK,             //重新对讲
    OC_STATE_INDUSTRYPLTM_STOP_TALK_FAILED,         //停止对讲失败
    OC_STATE_INDUSTRYPLTM_STOP_TALK_SUCCESS,        //停止对讲成功
    OC_STATE_INDUSTRYPLTM_TALK_EXCEPTION,           //对讲异常
};

#pragma mark - 播放状态回调 when type == OC_RESULT_PROTO_TYPE_DPSDK || OC_RESULT_PROTO_TYPE_Express || OC_RESULT_PROTO_TYPE_CloudBase || OC_RESULT_PROTO_TYPE_FINANCECLOUD || OC_RESULT_PROTO_TYPE_COMMUNITYCLOUD, code enum
typedef NS_ENUM(NSInteger, OC_INDUSTRYPLTM_PLAY_STATE)
{
    OC_STATE_INDUSTRYPLTM_PLAY_FIRSTSTREAM = 1,     // 获取到第一帧数据,可去显示播放画面了
    OC_STATE_INDUSTRYPLTM_PLAY_END,                 // 视频播放结束
    OC_STATE_INDUSTRYPLTM_PLAY_NETWORK_ABORT,       // 网络异常
    OC_STATE_INDUSTRYPLTM_PLAY_FAILED,              // 播放异常，检查播放视频数据错误
    OC_STATE_INDUSTRYPLTM_PLAY_BAD_FILE,            // 异常文件，不支持的文件格式
    OC_STATE_INDUSTRYPLTM_PLAY_SEEK_FAILED,         // 拖拽失败
    OC_STATE_INDUSTRYPLTM_PLAY_SEEK_SUCCESS,        // 拖拽成功
    OC_STATE_INDUSTRYPLTM_PLAY_CROSS_BORDER,        // 拖拽越界
    OC_STATE_INDUSTRYPLTM_PLAY_DATA_OVER,           // 所有文件播放结束
    OC_STATE_INDUSTRYPLTM_PLAY_AUTHORITY,           // 播放无权限
};

#pragma mark - 枚举LCOpenSDK_ERROR
typedef NS_ENUM(NSInteger, DssSDK_ERROR)
{
    //rest错误对外不做透传,一律为-1
    REST_ERROR_OUTSIDE = -1,
    REST_HTTP_ERR = -2,
    REST_BUSINESS_ERR = -3,
    REST_DATA_ERR = -4,
    
    NETSDK_ERROR_OUTSIDE = -1,
    
    ERROR_OK = 0,
    ERROR_FAIL = -1,
    ERROR_INVALID_PARAMETER  = -100,
    ERROR_REST_NOT_INIT,
    ERROR_UNSUPPORT_CALL,
};

#pragma mark - 全链路埋点
typedef NS_ENUM(NSInteger, OC_PLAY_STATE)
{
    OC_PLAY_STATE_START = 1,               //APP调用组件开始播放接口
    OC_PLAY_STATE_GETP2PPORT_BEGIN,        //开始获取p2p端口
    OC_PLAY_STATE_GETP2PPORT_OK,           //获取p2p端口成功
    OC_PLAY_STATE_GETP2PPORT_FAIL,         //获取p2p端口失败
    OC_PLAY_STATE_GETMTSURL_BEGIN,         //获取转发url开始
    OC_PLAY_STATE_GETMTSURL_OK,            //获取转发url成功
    OC_PLAY_STATE_GETMTSURL_FAIL,          //获取转发url结束
    OC_PLAY_STATE_GETSTREAM,               //调用流媒体接口开始
    OC_PLAY_STATE_FIRST_FRAME,             //收到第一帧数据
    OC_PLAY_STATE_PLAY_SUCCESS,            //playsdk渲染出第一帧
    OC_PLAY_STATE_STOP,                    //app调用关闭接口时间
};


#endif //__LCSDK_LCSDK_DEFINE_H__
