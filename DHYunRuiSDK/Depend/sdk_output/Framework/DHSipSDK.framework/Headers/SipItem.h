//
//  SipItem.h
//  ACEDrawingView
//
//  Created by 蒋成龙 on 2020/4/23.
//

#import <Foundation/Foundation.h>
#import <SipStackComponent/OCSipComponent.h>
#import "SipMobileServerInfo.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum:NSInteger {
    SipStatusUnRigester     = 0,
    SipStatusRigester       = 1,
    SipStatusRing           = 2,
    SipStatusTalking        = 3,
}SipStatus;

@interface SipItem : NSObject

@property (nonatomic, copy)   NSString             *key;
@property (nonatomic, assign) NSInteger            index;
@property (nonatomic, strong) SipMobileServerInfo  *param;
@property (nonatomic, strong) OCSipComponent       *sipComponent;
@property (nonatomic, assign) SipStatus             status;
@property (nonatomic, assign) BOOL                  isNeedChangeContact;

+ (instancetype)initWithKey:(NSString*)key index:(NSInteger)index param:(SipMobileServerInfo*)info component:(OCSipComponent*)sipComponent;
@end

NS_ASSUME_NONNULL_END
