//
//  DSSUnitInfo.h
//  Pods
//
//  Created by zyx on 17/3/17.
//
//

#import "DSSBaseInfo.h"

///unit type
typedef enum:NSUInteger {
    MBL_UNIT_UNKOWN,   ///< 未知 unknow
    MBL_UNIT_ENC,      ///< 编码 encoding
    MBL_UNIT_DEC,      ///< 解码 decoding
    MBL_UNIT_ALARMIN,  ///< 报警输入 alarm in
    MBL_UNIT_ALARMOUT, ///< 报警输出 alarm out
    MBL_UNIT_TVWALLIN, ///< TvWall输入 tvwall in
    MBL_UNIT_TVWALLOUT,///< TvWall输出 tvwall out
    MBL_UNIT_DOORCTRL, ///< 门禁 doorctrl
    MBL_UNIT_VOICE,    ///< 对讲 talk
    MBL_UNIT_PE,       ///< 动环PE,power environment(动力环境)
    MBL_UNIT_POS,      ///< POS机 POS
    MBL_UNIT_ROADGATE, ///< 道闸 road gate
    MBL_UNIT_LED,      ///< LED LED
    MBL_UNIT_PERIMETER,///< 周界 perimeter
    MBL_UNIT_RFID,     ///< RFID设备 RFID
    MBL_UNIT_DISPATCHER,///< 调度机 dispatcher
    MBL_UNIT_SIGNAL,    ///< 信号机
}MBL_UNIT_TYPE;

///人脸支持类型 face type
typedef enum:NSUInteger {
    MBL_FACE_UNSUPPORT,   ///< 不支持人脸 unsupport
    MBL_FACE_DETECTION,      ///< 检测 detection
    MBL_FACE_RECOGNITION,      ///< 识别 recognition
}MBL_FACE_TYPE;

///报警主机状态类型 alarmhost status
typedef enum:NSUInteger {

    MBL_ALARMHOST_STATUS_DEV_ARM,			///< 针对设备布防 arm
    MBL_ALARMHOST_STATUS_DEV_DISARM,		///< 针对设备撤防 disArm
    MBL_ALARMHOST_STATUS_DEV_IN_ARM,		///< 针对设备在家布防 arm in
    MBL_ALARMHOST_STATUS_DEV_OUT_ARM,		///< 针对设备外出布防 arm out
    MBL_ALARMHOST_STATUS_DEV_ALL,			///< 全局布防（新四路报警主机）arm all
    MBL_ALARMHOST_STATUS_DEV_INTIME,		///< 立即布防（新四路报警主机）arm intime
}MBL_ALARMHOST_STATUS_DEV;


//子系统状态类型定义 subsystem status
typedef enum:NSInteger{
    MBL_SUBSYSTEM_STATUS_ARM    = 1,     ////子系统布防状态
    MBL_SUBSYSTEM_STATUS_DISARM = 2,     ////子系统撤防状态
    MBL_SUBSYSTEM_STATUS_ARM_DELAY = 3,  ////子系统延时布防状态
    MBL_SUBSYSTEM_STATUS_DISARM_ABNORMAL = 4,     ////子系统异常撤防状态
    MBL_SUBSYSTEM_STATUS_ALL = 8, ///所有状态
} MBL_SUBSYSTEM_STATUS;

///单元分类，报警主机下面还会挂一个子系统的概念，其实就是同一种单元类型下的各个不同单元序号
///base unitInfo
@interface DSSBaseUnitInfo : DSSBaseInfo
@property (nonatomic, assign) MBL_UNIT_TYPE unitType; ///< unit type
@property (nonatomic, copy, nullable) NSString* name; ///< name
@property (nonatomic, copy, nullable) NSString* unitId; ///< unitId
@property (nonatomic, copy, nullable) NSString* parentid; ///< parentId
@property (nonatomic, strong, nullable) NSMutableArray<NSString*> *channels; ///< child channels

@end

@interface DSSAlarmInUnitInfo : DSSBaseInfo

@property (nonatomic, assign) MBL_ALARMHOST_STATUS_DEV unitState;///<布防撤防 unit state

@end

@interface DSSUnitInfo : DSSBaseUnitInfo

@property (nonatomic, strong, nullable) DSSAlarmInUnitInfo* alarmInUnitInfo; ///< alarmIn unitInfo

@end
