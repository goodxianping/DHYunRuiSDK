//
//  LCInitManager.h
//  RNMediaPlayer
//
//  Created by jiangChengLong on 2018/4/19.
//

#import <Foundation/Foundation.h>

@interface LCInitManager : NSObject

@property (atomic, copy)NSString* token;

+ (LCInitManager*)shareInstance;

+ (void)initOpenApi:(NSString*)addr port:(NSInteger)port CA_PATH:(NSString*)certPath key:(NSString*)key;

+ (void)Uninit;

+ (void)addPlayWinCount;

+ (void)delPlayWinCount;

- (NSInteger)request:(void*)req resp:(void*)resp timeout:(NSInteger)timeout;
@end
