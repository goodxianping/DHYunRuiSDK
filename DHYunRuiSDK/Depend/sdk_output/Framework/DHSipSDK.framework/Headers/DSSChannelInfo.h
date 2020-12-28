//
//  ChannelInfo.h
//  Pods
//
//  Created by zyx on 17/2/21.
//
//

#import <Foundation/Foundation.h>
#import "DSSBaseInfo.h"
#import "DSSUnitInfo.h"

#import <CoreLocation/CLLocation.h>

 /// 权限 channel right

typedef enum : NSUInteger {
    MBL_CHNL_RIGHT_NONE                 = 0x00000000,       ///<无任何权限  no right
    MBL_CHNL_RIGHT_MONITOR                = 0x00000001,        ///< 实时监视 monitor
    MBL_CHNL_RIGHT_PLAYBACK                = 0x00000002,        ///< 录像回放 playback
    MBL_CHNL_RIGHT_DOWNLOAD                = 0x00000004,        ///< 录像下载 record download
    MBL_CHNL_RIGHT_PTZ                    = 0x00000008,        ///< 云台控制 ptz control
    MBL_CHNL_RIGHT_DEV_VISIT            = 0x00000010,        ///< 设备直连 device visit
    MBL_CHNL_RIGHT_DEC_OUT                = 0x00000020,        ///< 解码输出 dec out
    MBL_CHNL_RIGHT_ALARM_INPUT            = 0x00000040,        ///< 报警输入 alarm input
    MBL_CHNL_RIGHT_ALARM_OUTPUT            = 0x00000080,        ///< 报警输出 alarm output
    MBL_CHNL_RIGHT_MAMUAL_CONTROL        = 0x00000100,        ///< 手动控制 mamual control
    MBL_CHNL_RIGHT_THIRD_DOOROUT        = 0x00000200,        ///< 第三方开门 third doorout
    MBL_CHNL_RIGHT_DOOR_MANAGE            = 0x00000400,        ///< 门禁管理 door manager
    MBL_CHNL_RIGHT_QUERY_INOUT_REGISTER    = 0x00000800,        ///< 进出门记录查询 query inout register
    MBL_CHNL_RIGHT_MIKE_USE                = 0x00001000,        ///< 话筒使用 microphone use
    MBL_CHNL_RIGHT_PIC_MONITOR            = 0x00002000,        ///< 图片监控 picture monitor
    MBL_CHNL_RIGHT_VOICE_TALK            = 0x00004000,        ///< 语音对讲 talk
    MBL_CHNL_RIGHT_VOICE_ALARMHOST        = 0x00008000,        ///< 报警主机（设备权限） alarmhost
    MBL_CHNL_RIGHT_PTZ_POINT            = 0x00010000,        ///< 预置点控制 ptz point
    MBL_CHNL_RIGHT_TVWALL                = 0x00020000,    ///< 电视墙 tvwall
    MBL_CHNL_RIGHT_PLAYBACK_PLATFORM    = 0x00040000,       ///< 录像回放（平台权限）playback (platform)
    MBL_CHNL_RIGHT_PLAYBACK_DEVICE      = 0x00080000,       ///< 录像回放(设备权限) playback (device)
    MBL_CHNL_RIGHT_DOWNLOAD_PLATFORM    = 0x00100000,       ///< 录像下载（平台权限）record download (platform)
    MBL_CHNL_RIGHT_DOWNLOAD_DEVICE      = 0x00200000,      ///< 录像下载（设备权限）record download (device)
    MBL_CHNL_RIGHT_SD_IDLEACT            = 0x00400000,      ///< 球机空闲动作配置
    
    //todo 本地自定义权限
    MBL_CHNL_RIGHT_CUSTOM_BAYONET = 0x01000000,  ///<卡口设备
    MBL_CHNL_RIGHT_CUSTOM_SIGNAL = 0x02000000,  ///<信号机设备
    MBL_CHNL_RIGHT_CUSTOM_GUOXIAN = 0x04000000, ///< 过线
    
} MBL_CHNL_RIGHT;

typedef enum:NSUInteger{
    MBL_CHANNEL_CAPABILITY_SMART =  0x00000001,    ///智能报警
    MBL_CHANNEL_CAPABILITY_FISHEYE =  0x00000002,    ///鱼眼矫正
    MBL_CHANNEL_CAPABILITY_GUOXIAN =  0x00000020, /// 过线
    MBL_CHANNEL_CAPABILITY_FACE_DETECTION   = 0x00000080,  //人脸检测
    MBL_CHANNEL_CAPABILITY_FACE_RECOGNITION = 0x00000100,  //人脸识别
    MBL_CHANNEL_CAPABILITY_OBJECT_CAPTURE   = 0x00000200,  //目标抓拍
}MBL_CHANNEL_CAPABILITY_TYPE;

//@"SmartAlarm"(智能报警)

#define SmartAlarm @"SmartAlarm"

@interface DSSBaseChannelInfo : DSSBaseInfo
@property (nonatomic, copy ,nullable) NSString* channelid;///< 通道id channelid
@property (nonatomic, copy ,nullable) NSString* name; ///< 名称 name
//@property (nonatomic, strong ,nullable) DHThreadSafeMultableArray<NSString *>* parentid; ///<父节点 parentId
@property (nonatomic, copy ,nullable) NSString* basicParentid;  ///<basic parentId
@property (nonatomic, assign) MBL_UNIT_TYPE chnlUnitType;///<单元类型 unit type
@property (nonatomic, assign) MBL_FACE_TYPE faceFunctionType;///<人脸识别能力类型 unit type

@property (nonatomic, copy,nullable) NSDictionary<NSString*,NSNumber*> *capability;///<能力集 unit type

@property (nonatomic,assign) NSUInteger nCapbilityRight; ///< 通道能力级 MBL_CHANNEL_CAPABILITY_TYPE 

@property (nonatomic, assign) NSUInteger nChnlRight; ///<MBL_CHNL_RIGHT 通道权限 channle right
@property (nonatomic, assign) BOOL isOnline; ///<在线状态 isOnline
@property (nonatomic, assign) CLLocationCoordinate2D location;///<坐标 location (map)

/**
 通道所属的设备id
 channel owned device

 @return 设备id deviceid
 */
-(NSString *_Nullable) deviceId;

@end


//-----------------------------------------------------------------------
//---------------------------begin---------------------------------------
//-----------------------------------------------------------------------
///摄像头类型 camera type
typedef enum:NSUInteger {
    MBL_CAMERA_TYPE_NORMAL,                        ///< 枪机 gunlock
    MBL_CAMERA_TYPE_SD,                            ///< 球机 SD Camera
    MBL_CAMERA_TYPE_HALFSD,                        ///< 半球 Half SD Camera
}MBL_CAMERA_TYPE;


/// 码流类型 stream type
typedef enum:NSUInteger {
    MBL_STREAM_TYPE_MAIN = 1, ///< 1-主码流
    MBL_STREAM_TYPE_SUB, ///< 2-辅码流
    MBL_STREAM_TYPE_THIRD,///< 3-三码流
}MBL_STREAM_TYPE;
///编码通道 encoding channleInfo
@interface DSSEncChannelInfo : DSSBaseInfo
@property (nonatomic, assign) NSTimeInterval lastVisitTime;       ///<用于历史记录; last visit time
@property (nonatomic, assign) MBL_CAMERA_TYPE cameretype; ///<摄像头类型  camere type
@property (nonatomic, assign) MBL_STREAM_TYPE streamtypeSupported;///<支持的码流类型，如果支持三码流，就一定支持主辅码流 Supported stream type
@property (nonatomic, copy ,nullable) NSString* cameraFunctions;  //通道能力集
@property (nonatomic, assign) int iTrackID;                        // 取流类型
@end

#define  MAX_STEP_PTZ_LENGTH 8
/// 云台控制方向命令 ptz deirection
typedef enum:NSUInteger {
    MBL_PTZ_DIRECTION_GO_UP                            = 1,                                ///< 上 up
    MBL_PTZ_DIRECTION_GO_DOWN,                                                            ///< 下 down
    MBL_PTZ_DIRECTION_GO_LEFT,                                                            ///< 左 left
    MBL_PTZ_DIRECTION_GO_RIGHT,                                                            ///< 右 right
    MBL_PTZ_DIRECTION_GO_LEFTUP,                                                            ///< 左上 leftup
    MBL_PTZ_DIRECTION_GO_LEFTDOWN,                                                        ///< 左下 leftdown
    MBL_PTZ_DIRECTION_GO_RIGHTUP,                                                            ///< 右上 rightup
    MBL_PTZ_DIRECTION_GO_RIGHTDOWN,                                                        ///< 右下 rightdown
    MBL_PTZ_DIRECTION_GO_CRUISE                        = 35,                                ///< 点间巡航命令 crusie
}MBL_PTZ_DIRECTION_GO;

/// 云台操作变倍、变焦、光圈  zoom\foucus\aperture
typedef enum:NSUInteger {
    MBL_PTZ_OPERATION_ADD_ZOOM,                                                            ///< 变倍+ zoom+
    MBL_PTZ_OPERATION_ADD_FOCUS,                                                          ///< 变焦+ focus+
    MBL_PTZ_OPERATION_ADD_APERTURE,                                                        ///< 光圈+ aperture+
    MBL_PTZ_OPERATION_REDUCE_ZOOM,                                                        ///< 变倍- zoom-
    MBL_PTZ_OPERATION_REDUCE_FOCUS,                                                        ///< 变焦- focus-
    MBL_PTZ_OPERATION_REDUCE_APERTURE,                                                    ///< 光圈- aperture-
}MBL_PTZ_OPERATION;

/// 三维定位
typedef enum:NSUInteger {
    MBL_PTZ_POSITION_NORMAL                           = 1,                                 ///< 普通定位
    MBL_PTZ_POSITION_PRECISION,                                                            ///< 精确定位
    MBL_PTZ_POSITION_RAYBALL,                                                              ///< 雷球定位
}MBL_PTZ_POSITION;

///预置点
@interface DSSPtzPrePointInfo : DSSBaseInfo

@property (nonatomic, copy ,nullable) NSString* channelid; ///<通道id channelid
@property (nonatomic, assign) int code; ///<code
@property (nonatomic, copy ,nullable) NSString* name; ///<名称 name
@property (nonatomic, assign) int type; ///<预置点类型 0普通预置点 1设置过智能规则的预置点 prepoint type

@end

//-----------------------------------------------------------------------
//---------------------------end-----------------------------------------
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
//---------------------------begin---------------------------------------
//-----------------------------------------------------------------------
/// 报警主机状态类型 alarmhost status type
typedef enum:NSUInteger {
    MBL_ALARMHOST_STATUS_CHL_BYPASS,        ///< 针对通道旁路 bypass
    MBL_ALARMHOST_STATUS_CHL_DISBYPASS,     ///< 针对通道取消旁路，表示正常状态 disbypass
    MBL_ALARMHOST_STATUS_CHL_ALARM,         ///< 报警；在取消旁路状态下，有可能会收到报警，就是报警状态 alarm
}MBL_ALARMHOST_STATUS_CHL;

///  alarm sensor type
typedef enum:NSUInteger {
    MBL_CHNL_ALARM_SENSOR_TYPE_ACOUSTOOPTIC           = 1,            ///<声光报警 sound and light alarm
    MBL_CHNL_ALARM_SENSOR_TYPE_PROCABIN_OPENED        = 2,            ///<防护舱打开  procabin opened
    MBL_CHNL_ALARM_SENSOR_TYPE_PROCABIN_LOCKED        = 3,            ///<防护舱锁死 procabin locked
    MBL_CHNL_ALARM_SENSOR_TYPE_LIGHT                  = 4,            ///<灯光 light
    MBL_CHNL_ALARM_SENSOR_TYPE_BUZZER                 = 5,            ///<蜂鸣器 buzzer
    MBL_CHNL_ALARM_SENSOR_TYPE_UNKNOWN                = 6,            ///<其他 unknow
}MBL_CHNL_ALARM_SENSOR_TYPE;

///alarmIn channelInfo
@interface DSSAlarmInChannelInfo : DSSBaseInfo

@property (nonatomic, assign) MBL_ALARMHOST_STATUS_CHL alarmhostChnlStatus;  ///< 报警主机状态类型 alarmhost channel status
@property (nonatomic, assign) MBL_CHNL_ALARM_SENSOR_TYPE nAlarmSensorType;///<报警传感器类型 alarm sensor type

@end

//-----------------------------------------------------------------------
//---------------------------end-----------------------------------------
//-----------------------------------------------------------------------
// 门禁信息  doorCtrl channelInfo
@interface DSSDoorControlChannelInfo : DSSBaseInfo
@property(nonatomic,assign) BOOL isOpen;
@property(nonatomic,assign) BOOL isAlwaysOpen;
@property(nonatomic,assign) BOOL isAlwaysClose;

@end
// 解码器信息 decoding channelInfo
@interface DSSDecChannelInfo : DSSBaseInfo
@property (nonatomic, assign) int decodeMode;   //解码模式 直连（1）、拉流（2）、推流给解码器（3）
@end

// TvWall输入通道
@interface DSSTVWallInChannelInfo : DSSBaseInfo
@end

// TvWall输出通道
@interface DSSTVWallOutChannelInfo : DSSBaseInfo
@property (nonatomic, assign) int decodeMode;   //解码模式 直连（1）、拉流（2）、推流给解码器（3）
@end

@interface DSSSignalChannelInfo : DSSBaseInfo
@property (nonatomic, assign) int serverId;   //服务器id
@property (nonatomic, assign) int manuId;   //产商编码
@property (nonatomic, assign) BOOL isSign;   //是否标记
@property (nonatomic, assign) NSInteger orderNumber;   //顺序
@property (nonatomic, assign) NSInteger trigerDis;   //触发距离
@property (nonatomic, copy) NSArray<NSString *>  * _Nullable relateChannels;   //触发距离

@end

@interface DSSChannelInfo : DSSBaseChannelInfo

@property (nonatomic, strong ,nullable) DSSEncChannelInfo* encChannelInfo;  ///< 编码器信息 encoding channelinfo
@property (nonatomic, strong ,nullable) DSSAlarmInChannelInfo* alarminChannelInfo;  ///< 报警输入信息 alarmin channelinfo
@property (nonatomic, strong ,nullable) DSSDoorControlChannelInfo* doorCtrlChannelInfo;  ///< 门禁信息  doorCtrl channelInfo
@property (nonatomic, strong ,nullable) DSSDecChannelInfo* decChannelInfo;  ///< 解码器信息 decoding channelInfo
@property (nonatomic, strong ,nullable) DSSTVWallInChannelInfo *tvWallInChannelInfo;
@property (nonatomic, strong ,nullable) DSSTVWallOutChannelInfo *tvWallOutChannelInfo;
@property (nonatomic, strong ,nullable) DSSSignalChannelInfo *signalChannelInfo;

@property (nonatomic, strong ,nullable) NSNumber* accessSource;
@property (nonatomic, strong ,nullable) NSNumber* unitSeq;
@end

