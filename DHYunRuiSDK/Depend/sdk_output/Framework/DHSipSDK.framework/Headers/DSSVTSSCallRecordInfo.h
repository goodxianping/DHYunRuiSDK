//
//  VTSSCallRecordInfo.h
//  Pods
//
//  Created by 28404 on 2017/12/13.
//

#import <Foundation/Foundation.h>
#import "DSSBaseInfo.h"

// 可视对讲接听状态
typedef NS_ENUM(NSInteger, CallRecordState) {
    CallRecordStateUnconnected  = 0,    // 未接通
    CallRecordStateConnected    = 1,    // 已接通
};

// 可视对讲开门状态
typedef NS_ENUM(NSInteger, OpenDoorState) {
    OpenDoorStateNotOpen    = 0,        // 未开过门
    OpenDoorStateOpen       = 1,        // 已开过门
};

// 通话记录类型
typedef NS_ENUM(NSInteger, CallRecordType) {
    CallRecordTypeIncoming = 0,         // 来电
    CallRecordTypeOutging,              // 去电
};

/**
 可视对讲通话记录
 */
@interface DSSVTSSCallRecordInfo : DSSBaseInfo <NSCoding>

@property (nonatomic, assign) long long infoId;   ///< 自定义ID，类似于数据库ID，从1开始递增
@property (nonatomic,copy  )NSString *contactTime;      ///< 时间
@property (nonatomic,copy  )NSString *contactName;      ///< 联系人名字
@property (nonatomic,copy  )NSString *contactNum;       ///< 联系人号码
@property (nonatomic,assign)CallRecordState callState;  ///< 接听状态
@property (nonatomic,assign)OpenDoorState openstate;    ///< 开门状态
@property (nonatomic,assign)CallRecordType recordType;  ///< 通话记录类型
@property (nonatomic, assign) int duration; // 通话时长
@property (nonatomic,copy  )NSString *durationStr;       ///< 通话时长字符串
@property (nonatomic, copy) NSString *callTypeStr; ///<呼叫类型 (0-呼入,1-呼出)
@property (nonatomic, copy) NSString *endStateStr; ///<呼叫状态 (0-未接,1-已接)
@end



