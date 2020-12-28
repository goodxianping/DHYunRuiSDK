//
//  DHAppDelegate.m
//  DHYunRuiSDK
//
//  Created by starryKey on 07/15/2020.
//  Copyright (c) 2020 starryKey. All rights reserved.
//

#import "DHAppDelegate.h"
#import <DHMediaPlay/DHMediaPlay-Swift.h>
#import <DHSipSDK/LCInitManager.h>
#import <DHSipSDK/SipManager.h>
 #import <IQKeyboardManager/IQKeyboardManager.h>

@implementation DHAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
     [IQKeyboardManager sharedManager].shouldResignOnTouchOutside = YES;
    [[DHMediaConfig shareInstance] setLogLevel:DHMediaLogLevelAll];
    [[DHMediaConfig shareInstance] setPlaySDKLogLevel:DHPlaySDKLogLevelDebug];
    NSString* cerPath = [[NSBundle mainBundle] pathForResource:@"cert" ofType:@"pem"];
    NSString* strAddr =  @"openapi.lechange.cn";
    NSString* LCKey = @"com.dahuatech.yys2LingShouYun:ReactNativeBase";
    [self initSDK:strAddr port:443 certPath:cerPath key:LCKey];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    [self uninitSDK];
}

- (void)initSDK:(NSString*)addr port:(NSInteger)port certPath:(NSString*)certPath key:(NSString*)key {
  NSString *safeCodeURL = [key stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
  [LCInitManager initOpenApi:addr port:port CA_PATH:certPath key: safeCodeURL];
}

- (void)uninitSDK {
  [SipManager destroyThreadPool];
  [LCInitManager Uninit];
}

@end
