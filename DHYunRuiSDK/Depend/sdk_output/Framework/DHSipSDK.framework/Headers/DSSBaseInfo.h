//
//  BaseInfo.h
//  SDKWeikit
//
//  Created by ding_qili on 15/7/13.
//  Copyright (c) 2015年 ding_qili. All rights reserved.
//

#import <Foundation/Foundation.h>
/**
 *  @author ding_qili, 15-10-23 10:10:07
 *
 *  @brief BaseInfo
 */
@interface DSSBaseInfo : NSObject
/**
 *  extended property
 */
@property (strong,nonatomic) NSMutableDictionary * attr;

/**
 *  add extended property
 *
 *  @param value value
 *  @param key   key
 */
- (void)addInfoObject:(NSObject *)value forKey:(NSString *)key;

/**
 *  get extended property
 *
 *  @param key key
 *
 *  @return value
 */
- (NSObject*)getInfoValueForKey: (NSString *)key;
@end
