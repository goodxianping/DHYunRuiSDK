//
//  SipErrorCode.h
//  SipCallBus
//
//  Created by 蒋成龙 on 2020/4/16.
//

#ifndef SipErrorCode_h
#define SipErrorCode_h

typedef enum:NSInteger {

    //临时应答(1XX)
    /** 100 Trying 正在处理中 **/
    kSipErrorCode_100 = 100,
    /** 180 Ringing 振铃 **/
    kSipErrorCode_180 = 180,
    /** 181 call being forwarder 呼叫正在前向 **/
    kSipErrorCode_181 = 181,
    /** 182 queue 排队 **/
    kSipErrorCode_182 = 182,

    //会话成功(2XX)
    /** 200 OK 会话成功 **/
    kSipErrorCode_200 = 200,

    //重定向(3XX)
    /** multiple 多重选择 **/
    kSipErrorCode_300 = 300,
    /** 301 moved permanently 永久移动 **/
    kSipErrorCode_301 = 301,
    /** 302 moved temporaily 临时移动 **/
    kSipErrorCode_302 = 302,
    /** 305 use proxy 用户代理 **/
    kSipErrorCode_305 = 305,
    /** 308 alternative service 替代服务 **/
    kSipErrorCode_380 = 380,

    //请求失败(4XX)
    /** 400 bad request 错误请求 **/
    kSipErrorCode_400 = 400,
    /** 401 unauthorized 未授权 **/
    kSipErrorCode_401 = 401,
    /** 402 payment required 付费要求 **/
    kSipErrorCode_402 = 402,
    /** 403 forbidden 禁止 **/
    kSipErrorCode_403 = 403,
    /** 404 not found 未发现 **/
    kSipErrorCode_404 = 404,
    /** 405 method no allowed 方法不允许 **/
    kSipErrorCode_405 = 405,
    /** 406 not acceptable 不可接受 **/
    kSipErrorCode_406 = 406,
    /** 407 proxy authentication required 代理需要认证 **/
    kSipErrorCode_407 = 407,
    /** 408 request timeout 请求超时 **/
    kSipErrorCode_408 = 408,
    /** 410 gone 离开 **/
    kSipErrorCode_410 = 410,
    /** 413 request entity too large 请求实体太大 **/
    kSipErrorCode_413 = 413,
    /** 414 request-url too long 请求URL太长 **/
    kSipErrorCode_414 = 414,
    /** 415 unsupported media type 不支持的媒体类型 **/
    kSipErrorCode_415 = 415,
    /** 416 unsupported url scheme 不支持的URL计划 **/
    kSipErrorCode_416 = 416,
    /** 420 bad extension 不良扩展 **/
    kSipErrorCode_420 = 420,
    /** 421 extension required 需要扩展  **/
    kSipErrorCode_421 = 421,
    /** 423 interval too brief 间隔太短 **/
    kSipErrorCode_423 = 423,
    /** 480 temporarily unavailable 临时失效 **/
    kSipErrorCode_480 = 480,
    /** call/transaction does not exist 呼叫/事务不存在 **/
    kSipErrorCode_481 = 481,
    /** 482 loop detected 发现环路 **/
    kSipErrorCode_482 = 482,
    /** 483 too many hops 跳数太多 **/
    kSipErrorCode_483 = 483,
    /** 484 address incomplete 地址不完整 **/
    kSipErrorCode_484 = 484,
    /** 485 ambiguous 不明朗 **/
    kSipErrorCode_485 = 485,
    /** 486 busy here 这里忙 **/
    kSipErrorCode_486 = 486,
    /** 487 request terminated 请求终止 **/
    kSipErrorCode_487 = 487,
    /** 488 not acceptable here 这里请求不可接受 **/
    kSipErrorCode_488 = 488,
    /** 491 request pending 未决请求 **/
    kSipErrorCode_491 = 491,
    /** 493 undecipherable 不可辨识 **/
    kSipErrorCode_493 = 493,

    //服务器失败(5XX)
    /** 500 server internal error 服务器内部错误 **/
    kSipErrorCode_500 = 500,
    /** 501 not implemented 不可执行 **/
    kSipErrorCode_501 = 501,
    /** 502 bad gateway 坏网关 **/
    kSipErrorCode_502 = 502,
    /** 503 service unavailable 服务无效 **/
    kSipErrorCode_503 = 503,
    /** 504 server time-out 服务器超时 **/
    kSipErrorCode_504 = 504,
    /** 505 version not supported 版本不支持 **/
    kSipErrorCode_505 = 505,
    /** 513 message too large 消息太大 **/
    kSipErrorCode_513 = 513,

    //全局性错误(6XX)
    /** 600 busy everywhere 全忙**/
    kSipErrorCode_600 = 600,
    /** 603 decline 丢弃 **/
    kSipErrorCode_603 = 603,
    /** 604 does not exist anywhere 不存在 **/
    kSipErrorCode_604 = 604,
    /** 606 not acceptable 不可接受 **/
    kSipErrorCode_606 = 606,

}emSipErrorCode;

#endif /* SipErrorCode_h */
