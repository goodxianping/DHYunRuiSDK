//
//  dssPubDefine.h
//  Pods
//
//  Created by chenfeifei on 2017/2/13.
//
//  idss公共定义文件
#import <Foundation/Foundation.h>
#import "DSSLocalizedHelper.h"

//适配iphoneX的新navigationbar高度
#define SafeAreaTopHeight (SCREEN_SIZE_HEIGHT == 812.0 ? 24 : 0)

#define SafeAreaBottomHeight (SCREEN_SIZE_HEIGHT == 812.0 ? 34 : 0)

#define SafeAreaLandscape ((SCREEN_SIZE_HEIGHT == 812.0 || SCREEN_SIZE_WIDTH == 812.0) ? 44 : 0)

//国际化 指定bundle
#define _T(str,bundle) [DSSLocalizedHelper localizedStringForKey:str table:@"Localizable" resourceBundle:bundle]

//主线程运行
#define RunOnMainThread(code)   {dispatch_async(dispatch_get_main_queue(), ^{code;});}

//加载指定bundle中的image
#define Image(name,bundle)    [UIImage imageNamed:name inBundle:bundle compatibleWithTraitCollection:nil]

//16进制颜色
#define HexRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]


#define SCREEN_SIZE_WIDTH     ([[UIScreen mainScreen]bounds].size.width)
#define SCREEN_SIZE_HEIGHT    ([[UIScreen mainScreen]bounds].size.height)
#define SAFE_SCREEN_SIZE_HEIGHT    (SCREEN_SIZE_HEIGHT - SafeAreaTopHeight - SafeAreaBottomHeight)


#define GET_CUR_LANGUAGE_TYPE   [[[NSUserDefaults standardUserDefaults] objectForKey:@"AppleLanguages"]objectAtIndex:0];

#define GET_USE_ADAPATER_REST_KEY  [[[[NSBundle mainBundle]infoDictionary]valueForKey:@"UseDataAdapterRest"]boolValue];

