//
//  DSSCallInfo.h
//  MobileBaseLineSDK
//
//  Created by huang_yundi on 2017/11/2.
//

#import <Foundation/Foundation.h>
typedef enum:NSInteger {
    CallTypeSignalCall = 0,
    CallTypeGroupCall,
    CallTypeVTCall,
}CallType;

// 呼叫业务状态
typedef enum:NSInteger {
    CallStatusPrepared = 0,
    CallStatusReqToSCS,
    CallStatusCalling,
    CallStatusRecving,
    CallStatusCeased,
}CallStatusType;


@interface DSSBaseParam : NSObject

@property (nonatomic, copy)   NSString*         key;
@property (nonatomic, assign) NSInteger         cid;
@property (nonatomic, copy)   NSString*         deviceID;

@end

@interface DSSCallInfo : DSSBaseParam

@property (nonatomic, assign) NSInteger         seq;                //序列号
@property (nonatomic, assign) NSInteger         audioSessionId;     //请求视频流当前音频session值
@property (nonatomic, assign) NSInteger         videoSessionId;     //请求视频session值
@property (nonatomic, assign) NSInteger         callbackState;      //上层下发模块ID,负数表示不标记，建议使用this指针
@property (nonatomic, assign) NSTimeInterval    requestTime;        //请求时间，用于超时检测
@property (nonatomic, copy)   NSString*         groupID;            //电话号码
@property (nonatomic, assign) NSInteger         tId;
@property (nonatomic, assign) BOOL              bState;             //呼叫状态

@end

@interface DSSInviteParam : DSSBaseParam

@property (nonatomic, assign) CallType          callType;
@property (nonatomic, copy)   NSString*         sendChannelID;
@property (nonatomic, copy)   NSString*         recvChannelID;
@property (nonatomic, copy)   NSString*         rtpServerIP;
@property (nonatomic, assign) NSInteger         rtpPort;
@property (nonatomic, assign) NSInteger         callID;
@property (nonatomic, assign) NSInteger         dialogID;
@property (nonatomic, assign) NSInteger         tID;
@property (nonatomic, assign) long              callState;

@end


