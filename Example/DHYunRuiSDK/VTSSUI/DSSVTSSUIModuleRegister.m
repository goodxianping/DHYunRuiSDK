//
//  DSSVTSSUIModuleRegister.m
//  Pods
//
//  Created by 28404 on 2017/11/06.
//
//

#import "DSSVTSSUIModuleRegister.h"
#import "DSSVTSSUIServiceProtocol.h"
#import "JLRoutes.h"
#import "JLRoutes+ViewController.h"


#import "DSSVTSSUIModuleHelper.h"
#import <IDHModule/IDHModule-umbrella.h>
#import "DHModuleEventDefine.h"
#import "DSSVTSSOutGoingCallViewController.h"
#import "DSSVTSSOutGoingCallViewModule.h"
#import "DSSCallSaver.h"
#import "Orientation.h"
#import <CoreTelephony/CTCallCenter.h>
#import <CoreTelephony/CTCall.h>

@interface DSSVTSSUIModuleRegister () <IDHModuleProtocol>

@property(nonatomic, strong) CTCallCenter *callCenter;

@end

@implementation DSSVTSSUIModuleRegister

+ (void)load
{
    [[IDHModuleManager sharedInstance]registerModule:@"DSSVTSSUIModuleRegister" module: [self class]];
}

- (id)init{
    if (self = [super init])
    {
        MTLOG(@"%@ %s", [self class], __FUNCTION__);
        self.callCenter = [[CTCallCenter alloc] init];
    }
    
    return self;
}

+ (NSArray<DTEventKey> *)onEventFilter{
    return @[DHMODULE_TRIGGER_EVENT_MOD_INIT];
}

- (void)onTriggerEvent:(DTEventKey)eventKey userInfo:(NSDictionary *)userInfo{
    if ([eventKey isEqualToString:DHMODULE_TRIGGER_EVENT_MOD_INIT]) {
        MTLOG(@"%@ %s", [self class], __FUNCTION__);
        [[JLRoutes globalRoutes] addRoute:kJLUrlVTSS_Call handler:^BOOL(NSDictionary * _Nonnull parameters) {
            dispatch_async(dispatch_get_main_queue(), ^{
                if (!self.callCenter.currentCalls.count && [[DSSCallSaver sharedInstance] canHandleCall]) {
                    NSValue *valueVC = [[IDHModuleManager sharedInstance] callModuleMethod:@"DSSCallViewController" methodKey:@"getViewController" args:nil];
                    id<DSSVTSSCallServiceProtocol> callVC = (id<DSSVTSSCallServiceProtocol>)valueVC.pointerValue;
                    callVC.notification = parameters[@"notification"];
                    if ([callVC isKindOfClass:[UIViewController class]]) {
                        UIViewController *callViewController = (UIViewController *)callVC;
                        [Orientation setOrientation:UIInterfaceOrientationMaskPortrait];
                        [[UIDevice currentDevice] setValue:[NSNumber numberWithInteger: UIDeviceOrientationUnknown] forKey:@"orientation"];
                        [[UIDevice currentDevice] setValue:[NSNumber numberWithInteger: UIDeviceOrientationPortrait] forKey:@"orientation"];
                        UIViewController *rootVC = [[self class] getPresentedViewController];
                        callViewController.modalPresentationStyle = UIModalPresentationFullScreen;
                        [rootVC presentViewController:callViewController animated:YES completion:nil];
                        [[DSSCallSaver sharedInstance] addCallOperationCount];
                    }
                } else {
                    // 如果当前已经有呼叫， 此处的呼叫直接拒接 ，门口机会提示忙线 // 如果当前没有小区编号 也直接拒接
                    DSSInviteVTParam *inviteParam = ((NSNotification *)(parameters[@"notification"])).object;
                    if (inviteParam) {
                        NSDictionary *dicParam= @{@"communityCode": inviteParam.fromAdr?:@"", @"callNum":inviteParam.userID?:@"", @"deviceId":inviteParam.deviceID?:@""};
                        [[DSSCallSaver sharedInstance] saveUnreceiveCaller:dicParam];
                        [[SipManager shareInstance] RejectDisturbWithKey:inviteParam.key withCid:inviteParam.cid];
                    }
                    
                }
            });
            return YES;
        }];
        
        [[JLRoutes globalRoutes] addRoute:kJLUrlVTSS_CallManager handler:^BOOL(NSDictionary * _Nonnull parameters) {
            dispatch_async(dispatch_get_main_queue(), ^{
                if (self.callCenter.currentCalls.count) {
                    TOAST_STRING(_T(@"In the call", BUNDLE_FOR_MODULE));
                } else {
                    if ([[DSSCallSaver sharedInstance] canHandleCall]) {
                        DSSVTSSOutGoingCallViewController *callManageVC = [[DSSVTSSOutGoingCallViewController alloc] init];
                        DSSVTSSOutGoingCallViewModule *callManageVM = [[DSSVTSSOutGoingCallViewModule alloc] initWithCommunityCode:parameters[@"communityCode"] withUniqueKey:parameters[@"uniqueKey"]];
                        callManageVC.viewModule = callManageVM;
                        callManageVC.modalPresentationStyle = UIModalPresentationFullScreen;
                        UIViewController *rootVC = [[self class] getPresentedViewController];
                        [rootVC presentViewController:callManageVC animated:YES completion:nil];
                        [[DSSCallSaver sharedInstance] addCallOperationCount];
                    }
                }
            });
            return YES;
        }];
    }
}

+ (UIViewController *)getPresentedViewController
{
    UIViewController *appRootVC = [UIApplication sharedApplication].delegate.window.rootViewController;
    UIViewController *topVC = appRootVC;
    while (topVC.presentedViewController) {
        topVC = topVC.presentedViewController;
    }
    return topVC;
}

@end
