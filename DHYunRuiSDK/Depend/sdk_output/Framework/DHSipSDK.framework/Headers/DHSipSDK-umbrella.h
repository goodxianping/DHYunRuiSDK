#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "DSSBaseInfo.h"
#import "DSSCallInfo.h"
#import "DSSCallVTInfo.h"
#import "DSSChannelInfo.h"
#import "DSSUnitInfo.h"
#import "DSSVTSSCallRecordInfo.h"
#import "HttpAPI+Extend.h"
#import "HttpAPI.h"
#import "HttpClient.h"
#import "LCInitManager.h"
#import "RemoteNotifyDefine.h"
#import "SipErrorCode.h"
#import "SipItem.h"
#import "SipManager.h"
#import "SipMobileServerInfo.h"

FOUNDATION_EXPORT double DHSipSDKVersionNumber;
FOUNDATION_EXPORT const unsigned char DHSipSDKVersionString[];

