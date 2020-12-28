//
//  CallVTInfo.h
//  MobileBaseLineSDK
//
//  Created by huang_yundi on 2017/11/2.
//

#import <Foundation/Foundation.h>
#import "DSSCallInfo.h"

typedef enum:NSInteger {
    CallAudioPCM    = 1,
    CallAudioG711   = 2,
    CallAudioG723   = 3,
    CallAudioG726   = 4,
    CallAudioG729   = 5,
}CallAudioType;

#pragma mark - Param
@interface DSSInviteVTParam : DSSBaseParam

@property (nonatomic, assign) CallType      callType;
@property (nonatomic, copy)   NSString*     userID;
@property (nonatomic, copy)   NSString*     rtpServerIP;
@property (nonatomic, assign) NSInteger     rtpAudioPort;
@property (nonatomic, assign) NSInteger     rtpVideoPort;
@property (nonatomic, assign) NSInteger     videoSessionID;
@property (nonatomic, assign) NSInteger     audioSessionID;
@property (nonatomic, assign) NSInteger     callID;
@property (nonatomic, assign) NSInteger     dialogID;
@property (nonatomic, assign) NSInteger     tID;
@property (nonatomic, assign) BOOL          bState;
@property (nonatomic, assign) CallAudioType audioType;
@property (nonatomic, assign) NSInteger     audioBits;          // 用实际的值表示，如8位 则填值为8
@property (nonatomic, assign) NSInteger     sampleRate;         // 采样率，如16k 则填值为16000
@property (nonatomic, copy)   NSString*     fromAdr;
@property (nonatomic, assign) BOOL          isAPP;

@end

@interface DSSStartVtParam : DSSBaseParam

@property (nonatomic, copy)   NSString*     userID;
@property (nonatomic, assign) CallType      callType;
@property (nonatomic, assign) CallAudioType audioType;
@property (nonatomic, assign) NSInteger     videoSessionID;
@property (nonatomic, assign) NSInteger     audioSessionID;
@property (nonatomic, assign) NSInteger     rtpVideoPort;
@property (nonatomic, assign) NSInteger     rtpAudioPort;

@end


@interface DSSStopVtParam : DSSBaseParam

@end

@interface DSSCancelVtParam : DSSBaseParam

@property (nonatomic, copy)   NSString*     userID;
@property (nonatomic, assign) NSInteger     videoSessionID;
@property (nonatomic, assign) NSInteger     audioSessionID;
@property (nonatomic, assign) NSInteger     callID;
@property (nonatomic, assign) NSInteger     dialogID;

@end

@interface DSSRingVtCallParam : DSSBaseParam

@property (nonatomic, copy)   NSString      *userID;
@property (nonatomic, assign) NSInteger     callID;
@property (nonatomic, assign) NSInteger     dialogID;
@property (nonatomic, assign) NSInteger     tId;

@end

@interface DSSBusyVtCallParam : DSSBaseParam

@property (nonatomic, copy)   NSString      *userID;
@property (nonatomic, assign) NSInteger     callID;
@property (nonatomic, assign) NSInteger     dialogID;
@property (nonatomic, assign) NSInteger     tId;

@end

@interface DSSScsAppNotifyParam : DSSBaseParam

@property (nonatomic, copy)   NSString      *message;

@end

#pragma mark - SipMessage
@interface DSSStartVtCallMsgParam : DSSBaseParam

@property (nonatomic, copy)   NSString*     userID;
@property (nonatomic, assign) CallType      callType;
@property (nonatomic, assign) CallAudioType audioType;
@property (nonatomic, assign) NSInteger     rtpVideoPort;
@property (nonatomic, assign) NSInteger     rtpAudioPort;
@property (nonatomic, assign) NSInteger     videoSessionID;
@property (nonatomic, assign) NSInteger     audioSessionID;
@property (nonatomic, assign) NSInteger     audioBits;          // 用实际的值表示，如8位 则填值为8
@property (nonatomic, assign) NSInteger     sampleRate;         // 采样率，如16k 则填值为16000
@property (nonatomic, assign) NSInteger     callID;
@property (nonatomic, assign) NSInteger     dialogID;
@property (nonatomic, assign) NSInteger     tID;
@property (nonatomic, assign) NSString*     sipIp;

@end

