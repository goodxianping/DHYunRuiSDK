//
//  LCOpenSDK_LoginManager.h
//  LCOpenSDK
//
//  Created by bzy on 2018/5/13.
//  Copyright © 2018 lechange. All rights reserved.
//

#ifndef LCOpenSDK_LoginManager_h
#define LCOpenSDK_LoginManager_h

#import <Foundation/Foundation.h>
#import "LCOpenSDK_Define.h"
@protocol LCOpenSDK_LoginManagerListener;
@protocol LCOpenSDK_LoginManagerNetSDKInterface;
@interface LCOpenSDK_LoginManager : NSObject

+ (LCOpenSDK_LoginManager*) shareMyInstance;

- (void)addDevices:(NSString*)token devicesJsonStr:(NSString*)devicesJsonStr failure:(void (^)(NSString* err))failure;

#pragma mark - 初始化接口
/**
 *  rest获取登陆组件和统计组件服务器信息并初始化
 *
 *  @param userName p2p服务器登录用户名
 *  @param passWord p2p服务器登录密码
 */
//- (NSInteger)initComponentWithP2pUserName:(NSString*)userName passWord:(NSString*)passWord;
/**
 *  初始化P2P服务
 *
 *  @param svrHost  p2p服务器地址
 *  @param svrPort  p2p服务器端口
 *  @param username p2p服务器登录用户名
 *  @param password p2p服务器登录密码
 *  @param isRelay  p2p relay开关
 *
 *  @return 0/非0 成功/失败
 */
- (NSInteger)initP2pSvrWithHost:(NSString*)svrHost svrPort:(ushort)svrPort username:(NSString*)username password:(NSString*)password isRelay:(BOOL)isRelay;
/**
 * 在addDevices之前,initP2pSvr之后调用
 * 增加p2p服务器，添加无用的服务会影响打洞性能
 */

- (NSInteger)addP2pSvrWithHost:(NSString*)svrHost svrPort:(ushort)svrPort username:(NSString*)username password:(NSString*)password isRelay:(BOOL)isRelay;

/**
 *  初始化统计(pss)服务
 *
 *  @param svrHost      统计服务器地址
 *  @param svrPort      统计服务器端口
 *  @param protocolType 统计服务协议类型
 - 0 HTTP
 - 1 HTTPS
 *  @param timeout      统计服务信令交互超时
 *
 *  @return 0/非0 成功/失败
 */
- (NSInteger)initReporterSvrWithHost:(NSString*)svrHost svrPort:(ushort)svrPort protocolType:(NSUInteger)protocolType timeout:(NSUInteger)timeout;

- (void)unInit;

#pragma mark - 预登陆相关接口
/**
 *  设置预打洞设备数量最大值
 *
 *  @param maxDeviceNum 预打洞设备数量最大值
 */
- (void)setMaxDeviceNum:(NSUInteger)maxDeviceNum;

/**
 *  添加设备信息
 *
 *  @param devicesJsonStr 设备信息字符串(Json格式)
 *         eg:[{"Sn":string, "Type":UINT,"Port":UINT,"User":string, "Pwd":string},{},...]
 *         Type:(0:大华P2P设备 1:乐橙设备)
 *
 *  @return YES/NO 成功/失败
 */
- (BOOL)addDevices:(NSString*)devicesJsonStr;

/**
 *  删除设备信息
 *
 *  @param devicesJsonStr 设备信息字符串(Json格式)
 *         eg:[{"Sn":string, "Type":UINT,"Port":UINT,"User":string, "Pwd":string},{},...]
 *         Type:(0:大华P2P设备 1:乐橙设备)
 *
 *  @return YES/NO 成功/失败
 */
- (BOOL)delDevices:(NSString*)devicesJsonStr;

/**
 *  删除所有设备信息
 *
 *  @return YES/NO 成功/失败
 */
- (BOOL)delAllDevices;

/**
 *  断开所有P2P链接
 *
 *  @return YES/NO 成功/失败
 *
 *  @note   网络断开(或者切换)时需要调用该接口
 */
- (BOOL)disConnectAll;

/**
 *  重连所有P2P链接
 *
 *  @return YES/NO 成功/失败
 *
 *  @note   网络重新连接时需要调用该接口
 */
- (BOOL)reConnectAll;

- (BOOL)disConnectByDevice:(NSString*)devID;
/**
 *  获取大华P2P设备NetSdk登陆句柄
 *
 *  @param deviceJsonStr 设备信息字符串(Json格式)
 *         eg:[{"Sn":string, "Type":UINT,"Port":UINT,"User":string, "Pwd":string},{},...]
 *         Type:(0:大华P2P设备 1:乐橙设备)
 *  @param isUseCache 是否只使用缓存获取netsdk handle
 *  @param timeout  接口超时时间(单位:毫秒)
 *
 *  @return 非nil/nil 成功/失败
 *
 *  @note   该接口为阻塞接口，阻塞时间为timeout
 */
- (void*)getNetSDKHandler:(NSString*)deviceJsonStr isUseCache:(BOOL)isUseCache timeout:(NSUInteger)timeout;

/**
 *  设置监听者，用来接收登录状态回调
 *
 *  @param lis 监听者实例(需遵守LCSDK_LoginManagerListener协议)
 */
-(void)setListener:(id<LCOpenSDK_LoginManagerListener>) lis;

-(BOOL)isRelay;

-(void)setClientId:(NSString*)clientId;

-(NSString*)getClientId;

/**
 *  获取设备P2P映射端口(用于RTSP协议拉流)
 *
 *  @param deviceJsonStr 设备信息字符串(Json格式)
 *         eg:{"Sn":string, "Type":UINT,"Port":UINT,"User":string, "Pwd":string}
 *         Type:(0:大华P2P设备 1:乐橙设备)
 *  @param timeout  接口超时时间(单位:毫秒)
 *
 *  @return 非0/0 成功/失败
 *
 *  @note   该接口为阻塞接口，阻塞时间为timeout
 */
- (NSUInteger)getP2PPort:(NSString*)deviceJsonStr timeout:(NSUInteger)timeout;

/**
 获取某台设备的P2P映射端口(需指定设备监听端口号)
 
 @param deviceSN 设备序列号
 @param port 设备监听端口号
 @param timeout 超时时间(单位毫秒)
 @return
 - >0 P2P映射端口
 - 0  映射失败
 @note  该接口为阻塞接口，由参数timeout控制超时时间
 */
- (NSUInteger)getP2PPort:(NSString*)deviceSN devicePort:(NSUInteger)port timeout:(NSUInteger)timeout;

/**
 接口调用失败后获取错误码
 
 @param deviceSN 设备序列号
 @param errDesc 错误码描述
 -对于不同的错误码，代表不同的含义
 -目前仅支持netsdk密码错误，errDesc表示剩余登陆次数（超过此次数会被锁定)
 
 @return 错误码(参考E_LOGIN_ERROR_CODE定义)
 */
- (E_LOGIN_ERROR_CODE)getErrNo:(NSString*)deviceSN errDesc:(NSString**)errDesc;

/**
 查询设备在线状态
 
 @param deviceSN 设备序列号
 @return 设备状态(参考E_DEVICE_STATE定义)
 */
- (E_DEVICE_STATE)getDevState:(NSString*)deviceSN p2pServer:(NSString**)serverInfoOut;

- (E_DEVICE_STATE)getDevState:(NSString*)deviceSN p2pServer:(NSString**)serverInfoOut isQueryCache:(BOOL)isQueryCache;

/**
 返回设备状态(对于NetSDK有效)
 
 @param deviceSN 设备序列号
 @return 返回设备状态信息的json字符串
 - 成功:json格式如下
 {
 "InPortNum":,       // DVR报警输入个数
 "OutPortNum":0,     // DVR报警输出个数
 "DiskNum":0,        // DVR硬盘个数
 "DVRType":0,        // DVR类型,见枚举NET_DEVICE_TYPE
 "ChanNum":0,        // DVR通道个数
 "LimitLoginTime":0, // 在线超时时间,为0表示不限制登陆,非0表示限制的分钟数
 "LeftLogTimes":0,   // 当登陆失败原因为密码错误时,通过此参数通知用户,剩余登陆次数,为0时表示此参数无效
 "LockLeftTime":0,   // 当登陆失败,用户解锁剩余时间（秒数）, -1表示设备未设置该参数
 }
 - 失败：空
 */
- (NSString*)getDevLogInfo:(NSString*)deviceSN;

/**
 设置netsdk登录接口
 
 @return
 */
- (void)setNetSDKLogin:(id<LCOpenSDK_LoginManagerNetSDKInterface>)netsdkLogin;

/**
 通知netsdk登录结果
 json格式如下
 {
 "InPortNum":,     // DVR报警输入个数 [成功]
 "OutPortNum":0,     // DVR报警输出个数 [成功]
 "DiskNum":0,        // DVR硬盘个数 [成功]
 "DVRType":0,        // DVR类型,见枚举NET_DEVICE_TYPE [成功]
 "ChanNum":0,        // DVR通道个数 [成功]
 "LimitLoginTime":0, // 在线超时时间,为0表示不限制登陆,非0表示限制的分钟数 [成功]
 "LeftLogTimes":0,   // 当登陆失败原因为密码错误时,通过此参数通知用户,剩余登陆次数,为0时表示此参数无效 [成功]
 "LockLeftTime":0,   // 当登陆失败,用户解锁剩余时间（秒数）, -1表示设备未设置该参数 [成功]
 "Loginhandle": "" // netsdk 登陆成功时返回的句柄 [成功]
 “error”: int        // netsdk 登录失败时的错误码 成功为 0，失败直接透传netsdk给组件
 "deviceSn": ""      // 设备序列号
 }
 **/
- (void)notifyLoginResult:(NSString*)LoginResult;

/**
 开启OZ P2P
*/
-(BOOL)startOzP2P:(NSString*)path;

/**
 关闭OZ P2P，释放netsdk handle
*/
-(BOOL)destroyNetSDKHandleByOZ:(NSString*)deviceID;

/**
 获取OZ设备登陆句柄
*/
-(void*)getNetSDKHandleByOZ:(NSString*)deviceSeq devID:(NSString*)deviceID user:(NSString*)user psw:(NSString*)psw port:(NSInteger)port timeout:(NSInteger)timeout LogInfo:(NSString**)devLogInfo;


- (BOOL)setSessionInfo:(NSInteger)localPort IP:(NSString*)ip Port:(NSInteger)port RequestId:(NSString*)requestId DeviceSn:(NSString*)deviceSn;

//p2p of TUTK
- (int)initTUTKP2P:(int)maxConnectionAllowed;
- (int)uninitTUTKP2P;
- (void *)getNetSDKHanlerByTUTK:(NSString *)uid userName:(NSString *)userName passWord:(NSString *)passWord localPort:(int)localPort remotePort:(int)remotePort timeOut:(int)timeOut logInfoOut:(NSString **)logInfoOut;
- (void)setTUTKP2PLogPath:(NSString *)path maxSize:(int)maxSize;
//p2p of TUTK

@end

#endif /* LCOpenSDK_LoginManager_h */
