//
//  ISipListener.h
//  SIPStackComponent
//
//  Created by Chenjian on 2019/5/5.
//  Copyright © 2019年 Dahua. All rights reserved.
//

#ifndef OCSipListener_h
#define OCSipListener_h
@protocol OCSipListener <NSObject>
@required
-(void) onRegisterStatus:(int)status sipIndex:(NSInteger)index;
-(void) onRegisterResult:(int)status regRspInfo:(NSString *)rspinfo sipIndex:(NSInteger)index;
-(void) onCallingOutcallback:(int)status cid:(int)cid liveStreamInfo:(NSString*)liveStreamInfo sipIndex:(NSInteger)index;
-(void) onCallingIncallback:(int)result cid:(int)cid liveStreamInfo:(NSString*)liveStreamInfo sipIndex:(NSInteger)index;
-(void) onCallingByecallback:(int)result cid:(int)cid liveStreamInfo:(NSString*)liveStreamInfo sipIndex:(NSInteger)index;
-(void) onOutcallcallback:(int)result cid:(int)cid callInfo:(NSString*)callInfo sipIndex:(NSInteger)index;
-(int) isCarryPAI:(int)status sipIndex:(NSInteger)index;
@end

#endif /* OCSipListener_h */
