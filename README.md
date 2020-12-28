 # iOS SDK 概述

## 使用提示

本文是 Sip呼叫SDK 标准的集成指南文档。用以指导 SDK 的使用方法，默认读者已经熟悉 IDE（ xcode ）的基本使用方法，以及具有一定的 OC和Swift 编程知识基础以及CocoaPods的集成知识基础。

本iOS SDK支持的最低系统版本为10，即`iOS 10` Swift版本要求为5.0，即`Swift5.0`

## 产品功能说明

本SDK基于H8900、H500平台或者云睿纯云模式，可以快速实现门口机呼叫手机App或者手机App呼叫管理机(PC客户端)，呼叫功能是基于Sip协议开发，开发者无需知晓协议实现细节即可完成呼叫相关功能开发

### Demo功能说明

- 门口机呼叫App、App呼叫管理中心(PC端)、远程开门等功能
- 呼叫过程中门口机视频预览、实时语音对讲等功能

### 呼叫集成说明

开发者集成Sip SDK 到其应用里，Sip SDK 创建到 Sip连接及保持心跳，为 App 提供设备在线的能力。 当开发者想要及时地将呼叫送达 App 时，只需要将呼叫号码等信息获取到后再调用sdk中的初始化接口即可轻松实现设备/App或者PC端/App间的呼叫交流。

图中红色部分，是 Sip SDK 与 App 开发者的接触点。手机客户端侧，App 需要集成 Sip SDK，同时需要通过OpenApi获取呼叫号码。

## **步骤一：在工程中导入sdk**

解压DHYunRuiSDK_xxx.zip，将解压后DHYunRuiSDK 目录拷贝到您的应用工程模块中,使用cocoaPod导入SDK。

Podfile文件新增。
```
pod 'DHYunRuiSDK', :path => '../DHYunRuiSDK'
```

Podfile相关依赖。
```
'MBProgressHUD'
'ReactiveObjC','3.0.0'
```

然后Podfile的目录下终端在执行
```
pod install
```

DHYunRuiSDK目录:
```
DHYunRuiSDK
|_____Pods.xcodeproj
|_____DHYunRuiSDK
| | |____Depend
| | | |____Bundle
| | | |____Framework
|_____DHYunRuiSDK.podspec
|_____Example             ------(DEMO)
|_____LICENSE
|_____README.md
```

## 步骤二：获取access_token

```Objective-C
        接口：/gateway/auth/oauth/token
    参数：
        client_id                云睿平台开发者服务中提供的client_id
        client_secret        云睿平台开发者服务中提供的client_ secret
        grant_type            默认传client_credentials
        scope                        默认传server
    返回值：
    access_token         云睿平台接口鉴权所需token
```

* 调用接口，获取接下来云睿相关请求所需携带的token

## 步骤三：初始化注册sip服务

* INIT

```Objective-C
  // 云平台
    NSNumber *cloudPersonSource = @1;
    SipMobileServerInfo* cloudSipInfo  = [[SipMobileServerInfo alloc] init];
    cloudSipInfo.expireTime            = 30; //信令超时时间
    cloudSipInfo.keepAliveTime         = 30; // 保活时间
    cloudSipInfo.localSipPort          = 37070; //任意本地端口
    cloudSipInfo.primarySipServer      = self.sipAddTextfield.text; // IP
    cloudSipInfo.serverSipPort         = [self.sipPortTextfield.text integerValue]; // 端口
    cloudSipInfo.account               = self.phoneNumberTextField.text; // 账户
    // SN呼入时拿到
    cloudSipInfo.userAgent             = [NSString stringWithFormat: @"%@ SN:%@", @"APPClient", self.phoneNumberTextField.text];
    NSString *cloudUniqueKey = [NSString stringWithFormat:@"%@:%@",self.sipAddTextfield.text, self.sipPortTextfield.text];
    [[SipManager shareInstance] addSipserver:cloudSipInfo withKey:cloudUniqueKey changeContact:[cloudPersonSource boolValue]];
    
    // 混合云
    NSNumber *hybridCloudPersonSource = @0;
    SipMobileServerInfo* hybridCloudSipInfo  = [[SipMobileServerInfo alloc] init];
    hybridCloudSipInfo.account               = self.hybridCloudphoneTextfield.text;//@"18969134312";
    hybridCloudSipInfo.expireTime            = 30;
    hybridCloudSipInfo.keepAliveTime         = 30;
    hybridCloudSipInfo.localSipPort          = 37777; //任意本地端口
    hybridCloudSipInfo.primarySipServer      = self.hybridCloudIPTextfield.text;
    hybridCloudSipInfo.serverSipPort         = [self.hybridCloudPortTextfield.text integerValue]; // 5082
    hybridCloudSipInfo.account               = self.hybridCloudphoneTextfield.text;
    // SN呼入时拿到
    hybridCloudSipInfo.userAgent             = [NSString stringWithFormat: @"%@ SN:%@", @"APPClient", self.hybridCloudphoneTextfield.text];
    NSString *hybridCloudUniqueKey = [NSString stringWithFormat:@"%@:%@",self.hybridCloudIPTextfield.text, self.hybridCloudPortTextfield.text];
    [[SipManager shareInstance] addSipserver:hybridCloudSipInfo withKey:hybridCloudUniqueKey changeContact:[hybridCloudPersonSource boolValue]];
```
* 然后监听相关回调
```Objective-C
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(cscConnected) name:VT_CALL_ACTION_EVENT_REGISTER object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(incomingCall:) name:VT_CALL_ACTION_EVENT_INVITE object:nil];
```


## 步骤四：反初始化

* UNINIT

```Objective-C
[[SipManager shareInstance] removeAll];
```

## 步骤五：SDK初始化

```Objective-C
// 步骤四中的 realmName
NSString* strAddr =  @"openapi.lechange.cn";
// 步骤四中的 iosCode
NSString* LCKey = @"com.dahuatech.yysH2LingShouYun:ReactNativeBase";
[LCInitManager initOpenApi:addr port:443 key: LCKey];
```

## 最后一步：SDK反初始化

```Objective-C
[LCInitManager Uninit];
```


## 呼叫功能调用说明

### 主动拨号调用

```Objective-C
/// 发起呼叫
/// @param uniqueKey 唯一标识
/// @param phoneNumber 电话号码
/// @param communityCode 社区编码
- (void) Calling:(NSString*)uniqueKey phoneNumber:(NSString*)phoneNumber communityCode:(NSString*)communityCode;
```
### 被动呼叫唤起

* 被动呼叫sdk中会自动唤起，无需任何操作 只需监听回调
```Objective-C
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(incomingCall:) name:VT_CALL_ACTION_EVENT_INVITE object:nil];
```

## Demo使用步骤说明
1.将Demo首页界面中的信息替换成现场环境对应信息
```Objective-C
    cloudSipInfo.primarySipServer      = self.sipAddTextfield.text;
    cloudSipInfo.serverSipPort         = [self.sipPortTextfield.text integerValue]; // 5082
    cloudSipInfo.account               = self.phoneNumberTextField.text;


    hybridCloudSipInfo.primarySipServer      = self.hybridCloudIPTextfield.text;
    hybridCloudSipInfo.serverSipPort         = [self.hybridCloudPortTextfield.text integerValue]; // 5082
    hybridCloudSipInfo.account               = self.hybridCloudphoneTextfield.text;

    [[HttpAPI shareInstance] setHost:@"https://www.cloud-dahua.com/gateway"];
```
2.点击初始化LOGIN按钮，为了获取鉴权的token、userId、小区编码，第三方可以通过自己的服务进行获取相关信息(三方使用可以去云睿开发平台找对应的接口来获取)

3.点击初始化Init按钮，初始化SIP服务

4.点击UNINIT按钮，移除SIP服务

```Objective-C
[[SipManager shareInstance] removeAll];
```
5. 主动呼叫需要配置communityCode uniqueKey

```Objective-C
    DSSVTSSOutGoingCallViewModule *callManageVM = [[DSSVTSSOutGoingCallViewModule alloc] initWithCommunityCode:@"b27ba7400d204bb488f2ea01b002cbb9" withUniqueKey:cloudUniqueKey];
```
6.被动呼叫
```Objective-C
        //登录鉴权token
        [DHDataCenter shareInstance].token =self.token;
        //下级需要（下级呼叫时带的有）
        [DHDataCenter shareInstance].communityCode = @"b27ba7400d204bb488f2ea01b002cbb9";
        // 可为空
        [DHDataCenter shareInstance].userId = @"";
        // 服务地址
        [DHDataCenter shareInstance].serviceHost = self.sipAddTextfield.text;//@"siptest.cloud-dahua.com";
        // 公司ID
        [DHDataCenter shareInstance].companyID = @"10";
        // 人员ID
        [DHDataCenter shareInstance].personFileID = @"490540956573970432";
        // lcToken用于播放视频
        [DHDataCenter shareInstance].lcToken = @"Ut_0000474b228db13a49a7b911a1e51ffb";
        // 手机号
        [DHDataCenter shareInstance].phoneNumber = self.phoneNumberTextField.text;
        
        [[HttpAPI shareInstance] setHost:@"https://www.cloud-dahua.com/gateway"];
        [[HttpAPI shareInstance] setToken:self.token];
```

## 常见错误说明

### 1.初始化失败

1.安全码错误。——检查SDK初始化参数是否正确。

2.网络连接错误——检查手机网络、服务IP或CMS端口是否正确
### 2.呼叫无法收到

a.网络连接问题——检查手机网络、服务器IP或者SIP端口是否正确

b.门口机设置问题——检查门口机是否正确添加到平台，门口机相关配置是否正确，门口机及平台是否显示为在线状态

### 注意事项
1.BuildSetting中`Enable Bitcode` 设置NO。


## 呼叫流程说明

### 监听事件类型
```
extern NSString *const VT_CALL_ACTION_EVENT_REGISTER ;  ///< 注册CSC
extern NSString *const VT_CALL_ACTION_EVENT_STOP ;      ///< 停止可视对讲
extern NSString *const VT_CALL_ACTION_EVENT_INVITE;     ///< 请求可视对讲
extern NSString *const VT_CALL_ACTION_EVENT_CANCEL;     ///< 主叫方取消呼叫（未接通前取消或客户端超时未接听）
extern NSString *const VT_CALL_ACTION_EVENT_BYE;        ///< VTO挂断已接通的通话
extern NSString *const VT_CALL_ACTION_EVENT_RING;       ///< 对方响铃
extern NSString *const VT_CALL_ACTION_EVENT_BUSY;       ///< 对方忙线
extern NSString *const VT_CALL_ACTION_MESSAGE_START;    ///< 对方接听
```

#### 添加SIP服务
```
/// @param info SIP详情
/// @param uniqueKey 唯一标识（用于区分不同的SIP）
/// @param isNeedChanged 是否需要变化(云为YES)
- (void) addSipserver:(SipMobileServerInfo*)info withKey:(NSString*)uniqueKey changeContact:(BOOL) isNeedChanged;
```

1.SipMobileServerInfo
```
@property (nonatomic, copy)  NSString* account;  // 账户
@property (nonatomic, assign)  NSInteger expireTime;  // //信令超时时间
@property (nonatomic, assign)  NSInteger keepAliveTime; // 保活时间
@property (nonatomic, assign)  NSInteger localSipPort;  //任意本地端口
@property (nonatomic, copy)  NSString* primarySipServer; // IP
@property (nonatomic, assign)  NSInteger serverSipPort; // 端口
@property (nonatomic, copy)  NSString* userAgent; // [NSString stringWithFormat: @"%@ SN:%@", @"APPClient", self.phoneNumberTextField.text]; 拼接
```

2.uniqueKey
```
[NSString stringWithFormat:@"%@:%d",primarySipServer, serverSipPort;
```

#### 通过key移除SIP
```
/// @param uniqueKey 唯一表识
- (void) removeByKey:(NSString*)uniqueKey;
```

#### 移除全部
```
- (void) removeAll;
```

#### 发起呼叫
```
/// @param uniqueKey 唯一标识
/// @param phoneNumber 电话号码
/// @param communityCode 社区编码
- (void) Calling:(NSString*)uniqueKey phoneNumber:(NSString*)phoneNumber communityCode:(NSString*)communityCode;
```

#### 重新呼叫
```
/// @param uniqueKey 唯一标识
/// @param cid sip标识
- (void) ReCallingWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;
```

#### 接听
```
/// @param uniqueKey 唯一标识
/// @param cid sip标识
- (void) AcceptCallingWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;
```

#### 拒接
```
/// @param uniqueKey 唯一标识
/// @param cid sip标识
- (void) RejectCallingWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;
```

#### 主动挂断
```
/// @param uniqueKey 唯一标识
/// @param cid sip标识
- (void) HangUpCallingWithKey:(NSString*)uniqueKey withCid:(NSInteger)cid;
```