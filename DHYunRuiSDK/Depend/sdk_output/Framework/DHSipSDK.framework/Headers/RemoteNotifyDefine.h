//
//  RemoteNotifyDefine.h
//  MobileBaseLineProxy
//
//  Created by chenfeifei on 2018/2/6.
//
#import <Foundation/Foundation.h>

extern NSString *const VT_CALL_ACTION_EVENT_REGISTER ;  ///< 注册CSC
extern NSString *const VT_CALL_ACTION_EVENT_STOP ;      ///< 停止可视对讲
extern NSString *const VT_CALL_ACTION_EVENT_INVITE;     ///< 请求可视对讲
extern NSString *const VT_CALL_ACTION_EVENT_CANCEL;     ///< 主叫方取消呼叫（未接通前取消或客户端超时未接听）
extern NSString *const VT_CALL_ACTION_EVENT_BYE;        ///< VTO挂断已接通的通话
extern NSString *const VT_CALL_ACTION_EVENT_RING;       ///< 对方响铃
extern NSString *const VT_CALL_ACTION_EVENT_BUSY;       ///< 对方忙线
extern NSString *const VT_CALL_ACTION_MESSAGE_START;    ///< 对方接听
extern NSString *const VT_CALL_ACTION_MESSAGE_SCS_APP_NOTIFY;

extern NSString *const VT_CALL_ACTION_TRANSEFER;

extern NSString *const VT_CALL_ACTION_RECORD_REFRESH;    ///< 可视对讲模块接到记录消息推送刷新


extern NSString* const kJLUrlVTSS_Main;
extern NSString* const kJLUrlVTSS_Module_Main;
extern NSString* const kJLUrlVTSS_Call;
extern NSString* const kJLUrlVTSS_CallManager;
