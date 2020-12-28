/*
* Copyright (c) 2009, 浙江大华技术股份有限公司
* All rights reserved.
*
* 摘　要：SDK接口很多,定制或一些不常用的功能可以放入dhnetsdkEx.h,
*         对外提供 dhnetsdk.h,
*         定制项目额外提供 dhnetsdkEx.h
*/
//////////////////////////////////////////////////////////////////////////
#ifndef DHNETSDKEX_H
#define DHNETSDKEX_H

#include "netsdk.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 ** 常量定义
 ***********************************************************************/

/************************************************************************
 ** 枚举定义
 ***********************************************************************/

/************************************************************************
 ** 结构体定义
************************************************************************/

 //////////////////////////////////////透传扩展接口参数//////////////////////////////////////////////////////////////////
 
 // 透传类型
 typedef enum   tagNET_TRANSMIT_INFO_TYPE
 {
    NET_TRANSMIT_INFO_TYPE_DEFAULT,                 // 默认类型，即CLIENT_TransmitInfoForWeb接口的兼容透传方式
    NET_TRANSMIT_INFO_TYPE_F6,                      // F6纯透传
 } NET_TRANSMIT_INFO_TYPE;

 // CLIENT_TransmitInfoForWebEx输入参数
 typedef struct tagNET_IN_TRANSMIT_INFO
 {
    DWORD                   dwSize;                         // 用户使用该结构体，dwSize需赋值为sizeof(NET_IN_TRANSMIT_INFO)
    NET_TRANSMIT_INFO_TYPE  emType;                         // 透传类型
    char*                   szInJsonBuffer;                 // Json请求数据,用户申请空间
    DWORD                   dwInJsonBufferSize;             // Json请求数据长度
    unsigned char*          szInBinBuffer;                  // 二进制请求数据，用户申请空间
    DWORD                   dwInBinBufferSize;              // 二进制请求数据长度
 } NET_IN_TRANSMIT_INFO;

 // CLIENT_TransmitInfoForWebEx输出参数
 typedef struct tagNET_OUT_TRANSMIT_INFO
 {
    DWORD                   dwSize;                         // 用户使用该结构体时，dwSize需赋值为sizeof(NET_OUT_TRANSMIT_INFO)
    char*                   szOutBuffer;                    // 应答数据缓冲空间, 用户申请空间
    DWORD                   dwOutBufferSize;                // 应答数据缓冲空间长度
    DWORD                   dwOutJsonLen;                   // Json应答数据长度
    DWORD                   dwOutBinLen;                    // 二进制应答数据长度
 } NET_OUT_TRANSMIT_INFO;

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////异步纯透传结构体定义开始////////////////////////////////////////////////////////////////////////////////////////////
 // CLIENT_AttachTransmitInfo 上报信息回调
 typedef struct tagNET_CB_TRANSMIT_INFO
 {
     BYTE*              pBuffer;            // 数据缓冲地址，SDK内部申请空间
     DWORD              dwBufferSize;       // 数据缓冲总长度
     DWORD              dwJsonLen;          // Json数据长度
     DWORD              dwBinLen;           // 二进制数据长度
     BYTE               byReserved[512];    // 保留字节
 } NET_CB_TRANSMIT_INFO;

 // CLIENT_AttachTransmitInfo()回调函数原型，第一个参数lAttachHandle是CLIENT_AttachTransmitInfo返回值
 typedef int  (CALLBACK *AsyncTransmitInfoCallBack)(LLONG lAttachHandle, NET_CB_TRANSMIT_INFO* pTransmitInfo, LDWORD dwUser);

 // CLIENT_AttachTransmitInfo输入参数
 typedef struct tagNET_IN_ATTACH_TRANSMIT_INFO
 {
     DWORD                       dwSize;                         // 用户使用该结构体时，dwSize需赋值为sizeof(NET_IN_ATTACH_TRANSMIT_INFO)
     AsyncTransmitInfoCallBack   cbTransmitInfo;                 // 回调函数
     LDWORD				         dwUser;                         // 用户数据
     char*                       szInJsonBuffer;                 // Json请求数据,用户申请空间
     DWORD                       dwInJsonBufferSize;             // Json请求数据长度  `

 }NET_IN_ATTACH_TRANSMIT_INFO;

 // CLIENT_AttachTransmitInfo输出参数
 typedef struct tagNET_OUT_ATTACH_TRANSMIT_INFO
 {
     DWORD                   dwSize;                         // 用户使用该结构体时，dwSize需赋值为sizeof(NET_OUT_ATTACH_TRANSMIT_INFO)
     BYTE*                   szOutBuffer;                    // 应答缓冲地址,用户申请空间
     DWORD                   dwOutBufferSize;                // 应答缓冲总长度
     DWORD                   dwOutJsonLen;                   // 应答Json数据长度
     DWORD                   dwOutBinLen;                    // 应答二进制数据长度 
 } NET_OUT_ATTACH_TRANSMIT_INFO;

 // CLIENT_DetachTransmitInfo输入参数
 typedef struct tagNET_IN_DETACH_TRANSMIT_INFO
 {
     DWORD                   dwSize;                         // 用户使用该结构体时，dwSize需赋值为sizeof(NET_IN_DETACH_TRANSMIT_INFO)
     char*                   szInJsonBuffer;                 // Json请求数据,用户申请空间
     DWORD                   dwInJsonBufferSize;             // Json请求数据长度
 } NET_IN_DETACH_TRANSMIT_INFO;

 // CLIENT_DetachTransmitInfo输出参数
 typedef struct tagNET_OUT_DETACH_TRANSMIT_INFO
 {
     DWORD                   dwSize;                         // 用户使用该结构体时，dwSize需赋值为sizeof(NET_OUT_DETACH_TRANSMIT_INFO)
     char*                   szOutBuffer;                    // 应答数据缓冲空间, 用户申请空间
     DWORD                   dwOutBufferSize;                // 应答数据缓冲空间长度
     DWORD                   dwOutJsonLen;                   // 应答Json数据长度
 } NET_OUT_DETACH_TRANSMIT_INFO;

//////上海BUS//////
 
// 上海巴士控制类型， 对应CLIENT_ControlSpecialDevice接口
typedef enum tagNET_SPECIAL_CTRL_TYPE
{
    NET_SPECIAL_CTRL_SHUTDOWN_PAD,            // 关闭PAD命令, pInBuf对应类型NET_IN_SHUTDOWN_PAD*, pOutBuf对应类型NET_OUT_SHUTDOWN_PAD*
    NET_SPECIAL_CTRL_REBOOT_PAD,              // 重启PAD命令, pInBuf对应类型NET_IN_REBOOT_PAD*, pOutBuf对应类型NET_OUT_REBOOT_PAD*                 
} NET_SPECIAL_CTRL_TYPE;

 //////////////////////////////////////////////设备特殊配置结构体定义开始////////////////////////////////////////////////////////////////////////////////////////////
 // CLIENT_DevSpecialCtrl 特殊控制类型
 typedef enum tagEM_DEV_SPECIAL_CTRL_TYPE
 {
     DEV_SPECIAL_CTRL_TYPE_RECORD_FLUSH,                  // 缓存录像数据强制写入硬盘, pInBuf=NET_IN_RECORD_FLUSH_INFO* , pOutBuf=NET_OUT_RECORD_FLUSH_INFO*
 } EM_DEV_SPECIAL_CTRL_TYPE;
 
 // CLIENT_DevSpecialCtrl, 对应 DEV_SPECIAL_CTRL_TYPE_RECORD_FLUSH 输入参数
 typedef struct tagNET_IN_NET_IN_RECORD_FLUSH_INFO
 {
    DWORD                                      dwSize;       // 用户使用该结构体时，dwSize需赋值为sizeof(NET_IN_RECORD_FLUSH_INFO)               
    int                                        nChannel;     // 通道号
    NET_STREAM_TYPE                            emStreamType; // 码流类型, 有效类型 "main", "Extra1", "Extra2", "Extar3", "Snapshot"     
 }NET_IN_RECORD_FLUSH_INFO;

 // CLIENT_DevSpecialCtrl, 对应 DEV_SPECIAL_CTRL_TYPE_RECORD_FLUSH 输出参数
 typedef struct tagNET_OUT_RECORD_FLUSH_INFO
 {
     DWORD                                     dwSize;       // 用户使用该结构体时，dwSize需赋值为sizeof(NET_OUT_RECORD_FLUSH_INFO)              
 }NET_OUT_RECORD_FLUSH_INFO;
 
 //////////////////////////////////////////////设备特殊配置结构体定义结束////////////////////////////////////////////////////////////////////////////////////////////
 

typedef struct tagNET_IN_REBOOT_PAD
{
    DWORD               dwSize;                  // 用户使用该结构体时，dwSize 需赋值为 sizeof(NET_IN_REBOOT_PAD)
} NET_IN_REBOOT_PAD;

typedef struct tagNET_OUT_REBOOT_PADE
{
    DWORD               dwSize;                  // 用户使用该结构体时，dwSize 需赋值为 sizeof(NET_OUT_REBOOT_PAD)
} NET_OUT_REBOOT_PAD;

typedef struct tagNET_IN_SHUTDOWN_PAD
{
    DWORD               dwSize;                  // 用户使用该结构体时，dwSize 需赋值为 sizeof(NET_IN_REBOOT_PAD)
    int                 nDelayTime;              // 延时关机时间, 单位：秒
} NET_IN_SHUTDOWN_PAD;

typedef struct tagNET_OUT_SHUTDOWN_PAD
{
    DWORD               dwSize;                  // 用户使用该结构体时，dwSize 需赋值为 sizeof(NET_OUT_SHUTDOWN_PAD)
} NET_OUT_SHUTDOWN_PAD;

//////////////////////////////////////////////异步纯透传结构体定义结束////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////设备网卡信息结构体定义开始 ////////////////////////////////////////////////////////////////////////////////////////////

typedef struct tagNET_DHDEV_ETHERNET_INFO
{
    DWORD               dwSize;                                 // 用户使用该结构体时，dwSize 需赋值为 sizeof(NET_DHDEV_ETHERNET_INFO)
    int                 nEtherNetNum;                           // 以太网口数
    DH_ETHERNET_EX      stuEtherNet[DH_MAX_ETHERNET_NUM_EX];    // 以太网口
} NET_DHDEV_ETHERNET_INFO;

//////////////////////////////////////////////设备网卡信息结构体定义结束////////////////////////////////////////////////////////////////////////////////////////////


//获取HCDZ采集信息,输入参数
typedef struct tagNET_IN_HCDZ_LIST_INFO 
{
    DWORD                           dwSize;							//  结构体大小, 调用者必须初始化该字段
	UINT							nIndexNum;					   //数组szindex有效数量
    UINT                            szIndex[DH_COMMON_STRING_64]; //一个数组,index 值与通道下标对应
}NET_IN_HCDZ_LIST_INFO;

// HCDZ采集信息，检测模块采集信息
typedef struct tagNET_HCDZ_INFO 
{
    UINT            nChannelID;								// 通道号(从0开始)
    UINT            nAIMode;								// AI测量数据模式设置  0 表示输入数据0-10000对应0-100%输入 1 表示4-20mA测量方式，输入数据0-10000对应4-20mA(20%-100%AI量程)
	UINT            nAIO;									// 检测模块模拟输入通道量程 20表示20mA 5表示5V 10表示10V
	UINT			nAnalogInputNum;						// 有效的模拟量输入数量
    UINT            arrAnalogInput[DH_COMMON_STRING_8];     // 是一个数组,检测模块模拟量输入寄存器值 无符号数0-10000对应0-满量程；实际值=DATA/10000*量程AI0，单位mA或V 
	UINT			nDINum;						            // 有效的模模块开关量输入数量
    UINT            arrDI[DH_COMMON_STRING_4];              // 检测模块开关量输入值，是一个数组，0为关，1为开
	UINT			nDONum;						            // 有效的模块开关量输出数量
    UINT            arrDO[DH_COMMON_STRING_4];              // 检测模块开关量输出值，是一个数组，0为关，1为开
}NET_HCDZ_INFO;

// 获取HCDZ采集信息,输出参数
typedef struct tagNET_OUT_HCDZ_LIST_INFO 
{
    DWORD                       dwSize;                             // 结构体大小, 调用者必须初始化该字段
	UINT				        nValidNum;						    // 数组stuInfo的有效个数
    NET_HCDZ_INFO				stuInfo[DH_COMMON_STRING_64];       // HCDZ采集信息
}NET_OUT_HCDZ_LIST_INFO;

typedef struct tagNET_IN_HCDZ_CAPS 
{
    DWORD                           dwSize;                          // 结构体大小, 调用者必须初始化该字段
}NET_IN_HCDZ_CAPS;

// 获取HCDZ(惠测电子)能力结构体
typedef struct tagCFG_HCDZ_CAPS
{
	DWORD                               dwSize;                                 // 结构体大小, 调用者必须初始化该字段
	char								szModelID[DH_COMMON_STRING_32];		    // 设备型号
	unsigned int						nVersion;								// 版本
	unsigned int						nAnalogsNum;							// 检测模块模拟量输入个数
	unsigned int						nDINum;									// 检测模块开关量输入个数
	unsigned int						nDONum;									// 检测模块开关量输出个数
}NET_OUT_HCDZ_CAPS;

// 获取电梯状态(HADT山东金鲁班宏安电梯),输入参数
typedef struct tagNET_IN_HADT_STATUS
{
    DWORD                               dwSize;                                 // 结构体大小, 调用者必须初始化该字段
}NET_IN_HADT_STATUS;

// 获取电梯状态(HADT山东金鲁班宏安电梯),输出参数
typedef struct tagNET_OUT_HADT_STATUS
{
    DWORD                               dwSize;                                 // 结构体大小, 调用者必须初始化该字段
    int                                 nLevelSignal1;                          // 楼层信号值，用于获取楼层的个位数信息，范围(0~37)由客户获取值后自行解析
    int                                 nLevelSignal2;                          // 楼层信号值，用于获取楼层的十位数信息，范围(0~37)由客户获取值后自行解析
    int                                 nLevelSignal3;                          // 楼层信号值，用于获取楼层的百位数信息，范围(0~37)由客户获取值后自行解析 
    DWORD                               dwliftStatus;                           // 电梯状态信息，每一位代表一种状态
                                                                                // bit0: 地震；该位置1表示地震，置0表示没有地震
                                                                                // bit1: 自救；该位置1表示自救，置0表示没有自救
                                                                                // bit2: 满载；该位置1且bit3和bit12置0表示满载，其它表示无效
                                                                                // bit3: 超载；该位置1且bit2和bit12置0表示超载，其它表示无效
                                                                                // bit4: 消防；该位置1表示消防，置0表示没有消防
                                                                                // bit5: 检修；该位置1表示检修，置0表示没有检修
                                                                                // bit6: 下行；该位置1且bit7置0下行，其它表示无效
                                                                                // bit7: 上行；该位置1且bit6置0表示上行，其它表示无效
                                                                                // bit8: 语音报站；该位置1表示有语音报站，置0表示没有语音报站
                                                                                // bit12: 空载；该位置1且bit2和bit3置0表示空载，其它表示无效
                                                                                // bit13: 停止/运行；该位置1表示运行，置0表示停止
                                                                                // bit14: 关门；该位置1且bit15置0表示关门，其它表示无效
                                                                                // bit15: 开门；该位置1且bit14置0表示开门，其它表示无效
}NET_OUT_HADT_STATUS;

//报警输出控制接口CLIENT_SetAlarmOut，输入参数
typedef struct tagNET_IN_SET_ALARMOUT
{
    DWORD                               dwSize;                                 // 结构体大小，需要赋值
    int                                 nChannel;                               // 通道号，从0开始
    int                                 nTime;                                  // time > 0 时, time生效。单位:秒
    int                                 nLevel;                                 // time = 0 时, level生效。time与level都为0时，表示停止
}NET_IN_SET_ALARMOUT;

//报警输出控制接口CLIENT_SetAlarmOut，输出参数
typedef struct tagNET_OUT_SET_ALARMOUT
{   
    DWORD                               dwSize;                                 // 结构体大小,需要赋值
}NET_OUT_SET_ALARMOUT;

// 录像类型
typedef enum tagEM_NET_LINK_RECORD_EVENT
{
    EM_NET_LINK_RECORD_UNKNOWN,                         // 未知
    EM_NET_LINK_RECORD_ALARM,                           // Alarm
} EM_NET_LINK_RECORD_EVENT;

//CLIENT_StartLinkRecord输入参数
typedef struct tagNET_IN_LINK_RECORD_CTRL
{
    DWORD                       dwSize;                 // 该结构体大小
    unsigned int                nChannel;               // 通道号
    unsigned int                nLength;                // 录像时长
    EM_NET_LINK_RECORD_EVENT    emType;                 // 录像类型"Alarm"-报警录像，当前仅支持这种录像
} NET_IN_LINK_RECORD_CTRL;

//CLIENT_StartLinkRecord输出参数
typedef struct tagNET_OUT_LINK_RECORD_CTRL
{
    DWORD                       dwSize;                 // 该结构体大小
} NET_OUT_LINK_RECORD_CTRL;

// CLIENT_SetDeviceUkey输入参数
typedef struct tagNET_IN_SET_UEKY
{
    DWORD                       dwSize;                 // 该结构体大小
    char                        szUkey[128];             // Ukey号
}NET_IN_SET_UEKY;

// CLIENT_SetDeviceUkey 输出参数
typedef struct tagNET_OUT_SET_UEKY
{
    DWORD                       dwSize;                 // 该结构体大小
}NET_OUT_SET_UEKY;
/***********************************************************************
 ** 回调函数定义
 ***********************************************************************/

 /**************************************************************************************
 *   Funcname: fAsynPlayHandleCallBack
 *   Purpose:  异步实时监视回调函数
 *   InputParam:    LLONG                    :lPlayHandle // 实时监视播放句柄
 *   InputParam:    LLONG                    :lLoginID    // 登陆句柄
 *   InputParam:    int                      :nChannelID  // 通道号
 *   InputParam:    HWND                     :hWnd        // 窗口句柄
 *   InputParam:    LDWORD                   :dwUser      // 用户
 *   Created:%2015%:%12%:%23%  
 *   Revision Record:date:author:modify sth
**************************************************************************************/
typedef void (CALLBACK *fAsynPlayHandleCallBack)(LLONG lPlayHandle, LLONG lLoginID, int nChannelID, HWND hWnd, LDWORD dwUser);




/************************************************************************
 ** 接口定义
 ***********************************************************************/

/******************************************************************************
功能描述	:	下载录像文件--扩展,可加载码流转换库
输入参数	:	
    lLoginID:       登录接口返回的句柄
    lpRecordFile:   查询录像接口返回的录像信息
    sSavedFileName: 保存录像文件名,支持全路径
    cbDownLoadPos:  下载进度回调函数(回调下载进度,下载结果)
    dwUserData:     下载进度回调对应用户数据
    fDownLoadDataCallBack: 录像数据回调函数(回调形式暂不支持转换PS流)
    dwDataUser:     录像数据回调对应用户数据
    scType:         码流转换类型,0-DAV码流(默认); 1-PS流
    pReserved:      保留字段,后续扩展
输出参数	：	N/A
返 回 值	：	LLONG 下载录像句柄
其他说明	：	特殊接口,SDK默认不支持转PS流,需定制SDK
******************************************************************************/
CLIENT_NET_API LLONG CALL_METHOD CLIENT_DownloadByRecordFileEx2(LLONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, 
                                                    fDownLoadPosCallBack cbDownLoadPos, LDWORD dwUserData, 
                                                    fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser, 
                                                    int scType = 0, void* pReserved = NULL);

/******************************************************************************
功能描述	:	通过时间下载录像--扩展,可加载码流转换库
输入参数	:	
    lLoginID:       登录接口返回的句柄
    nChannelId:     视频通道号,从0开始
    nRecordFileType:录像类型0 所有录像文件
                            1 外部报警 
                            2 动态检测报警 
                            3 所有报警 
                            4 卡号查询  
                            5 组合条件查询 
                            6 录像位置与偏移量长度 
                            8 按卡号查询图片(目前仅HB-U和NVS特殊型号的设备支持) 
                            9 查询图片(目前仅HB-U和NVS特殊型号的设备支持)  
                            10 按字段查询 
                            15 返回网络数据结构(金桥网吧) 
                            16 查询所有透明串数据录像文件 
    tmStart:        开始时间 
    tmEnd:          结束时间 
    sSavedFileName: 保存录像文件名,支持全路径
    cbTimeDownLoadPos: 下载进度回调函数(回调下载进度,下载结果)
    dwUserData:     下载进度回调对应用户数据
    fDownLoadDataCallBack: 录像数据回调函数(回调形式暂不支持转换PS流)
    dwDataUser:     录像数据回调对应用户数据
    scType:         码流转换类型,0-DAV码流(默认); 1-PS流,3-MP4
    pReserved:      保留参数,后续扩展
输出参数	：	N/A
返 回 值	：	LLONG 下载录像句柄
其他说明	：	特殊接口,SDK默认不支持转PS流,需定制SDK
******************************************************************************/
CLIENT_NET_API LLONG CALL_METHOD CLIENT_DownloadByTimeEx2(LLONG lLoginID, int nChannelId, int nRecordFileType, 
                                                    LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, 
                                                    fTimeDownLoadPosCallBack cbTimeDownLoadPos, LDWORD dwUserData, 
                                                    fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser, 
                                                    int scType = 0, void* pReserved = NULL);

/******************************************************************************
功能描述	:	透传扩展接口,按透传类型走对应透传方式接口，目前支持F6纯透传, 同时兼容CLIENT_TransmitInfoForWeb接口
参数定义	:	
    lLoginID:       登录接口返回的句柄
    pInParam:       透传扩展接口输入参数
    pOutParam       透传扩展接口输出参数
    nWaittime       接口超时时间

返 回 值	：	BOOL  TRUE :成功; FALSE :失败
******************************************************************************/
CLIENT_NET_API BOOL  CALL_METHOD CLIENT_TransmitInfoForWebEx(LLONG lLoginID, NET_IN_TRANSMIT_INFO* pInParam, 
                                                             NET_OUT_TRANSMIT_INFO* pOutParam, int nWaittime = 3000);


/******************************************************************************
功能描述	:	 异步纯透传订阅接口
参数定义	:	
    lLoginID:       登录接口返回的句柄
    pInParam:       异步纯透传接口输入参数
    pOutParam       异步纯透传接口输出参数
    nWaittime       接口超时时间

返 回 值	：	    LLONG 异步纯透传句柄
******************************************************************************/
CLIENT_NET_API LLONG CALL_METHOD CLIENT_AttachTransmitInfo(LLONG lLoginID, const NET_IN_ATTACH_TRANSMIT_INFO* pInParam, NET_OUT_ATTACH_TRANSMIT_INFO* pOutParam, int nWaitTime);

 

/******************************************************************************
功能描述	:	 异步纯透传取消订阅接口
参数定义	:	
    lAttachHandle:  异步纯透传句柄，即CLIENT_AttachTransmitInfo接口的返回值
    pInParam:       异步纯透传取消订阅接口输入参数
    pOutParam       异步纯透传取消订阅接口输出参数
    nWaittime       接口超时时间

返 回 值	：		BOOL  TRUE :成功; FALSE :失败
******************************************************************************/
CLIENT_NET_API BOOL  CALL_METHOD CLIENT_DetachTransmitInfo(LLONG lAttachHandle, const NET_IN_DETACH_TRANSMIT_INFO* pInParam, NET_OUT_DETACH_TRANSMIT_INFO* pOutParam, int nWaitTime);


/******************************************************************************
功能描述	:	 设备特殊控制接口
参数定义	:	
    lLoginID:                       登录接口返回的句柄
    EM_DEV_SPECIAL_CTRL_TYPE:       特殊控制类型
    pInParam:                       设备特殊控制接口输入参数
    pOutParam                       设备特殊控制接口输出参数
    nWaittime                       接口超时时间

返 回 值	：		BOOL  TRUE :成功; FALSE :失败
******************************************************************************/
CLIENT_NET_API  BOOL CALL_METHOD CLIENT_DevSpecialCtrl(LLONG lLoginID, EM_DEV_SPECIAL_CTRL_TYPE emType, void* pInParam, void* pOutParam, int nWaitTime = 3000);


/******************************************************************************
功能描述	:	 获取设备网卡信息接口
参数定义	:	
    lLoginID:                       登录接口返回的句柄
    pstOutParam                     获取设备网卡信息接口的输出参数
    nWaittime                       接口超时时间

返 回 值	：		BOOL  TRUE :成功; FALSE :失败
******************************************************************************/
CLIENT_NET_API  BOOL CALL_METHOD CLIENT_QueryEtherNetInfo(LLONG lLoginID, NET_DHDEV_ETHERNET_INFO* pstuOutParam, int nWaitTime = 3000);


/**************************************************************************************
*   Funcname: CLIENT_StartAsynRealPlay
*   Purpose:开启异步实时监视接口
*   InputParam:    LLONG                    :lLoginID    // 登陆句柄
*   InputParam:    int                      :nChannelID  // 通道号
*   InputParam:    HWND                     :hWnd        // 窗口句柄
*   InputParam:    fAsynPlayHandleCallBack  :cbPlayHandle// 异步实时监视播放句柄回调
*   InputParam:    DH_RealPlayType          :rType       // 主码流类型
*   InputParam:    fRealDataCallBackEx      :cbRealData  // 实时监视数据回调函数
*   InputParam:    fRealPlayDisConnect      :cbDisconnect// 视频监视断开回调函数
*   InputParam:    LDWORD                   :dwUser      // 用户
*   InputParam:    DWORD                    :dwWaitTime  // 等待时间
*   Return:BOOL:FALSE,wrong;TRUE :right
*   Created:%2015%:%12%:%23%  
*   Revision Record:date:author:modify sth
**************************************************************************************/
CLIENT_NET_API BOOL CALL_METHOD CLIENT_StartAsynRealPlay(LLONG lLoginID, int nChannelID, HWND hWnd, fAsynPlayHandleCallBack cbPlayHandle, DH_RealPlayType rType, fRealDataCallBackEx cbRealData = NULL, fRealPlayDisConnect cbDisconnect = NULL, LDWORD dwUser = 0, DWORD dwWaitTime = 10000);

//////上海BUS//////

// 串口数据交互接口,异步获取数据
CLIENT_NET_API LLONG CALL_METHOD CLIENT_ExChangeData(LLONG lLoginId, NET_IN_EXCHANGEDATA* pInParam, NET_OUT_EXCHANGEDATA* pOutParam, int nWaittime = 5000);

// 监听CAN总线数据
CLIENT_NET_API LLONG CALL_METHOD CLIENT_AttachCAN(LLONG lLoginID, const NET_IN_ATTACH_CAN* pstInParam, NET_OUT_ATTACH_CAN* pstOutParam, int nWaitTime = 3000);

// 取消监听CAN总线数据，lAttachHandle是CLIENT_AttachCAN返回值
CLIENT_NET_API BOOL CALL_METHOD CLIENT_DetachCAN(LLONG lAttachHandle);

// 发送CAN总线数据
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SendCAN(LLONG lLoginID, const NET_IN_SEND_CAN* pstInParam, NET_OUT_SEND_CAN* pstOutParam, int nWaitTime = 3000);

// 监听透明串口数据
CLIENT_NET_API LLONG CALL_METHOD CLIENT_AttachDevComm(LLONG lLoginID, const NET_IN_ATTACH_DEVCOMM* pstInParam, NET_OUT_ATTACH_DEVCOMM* pstOutParam, int nWaitTime = 3000);

// 取消监听透明串口数据，lAttachHandle是CLIENT_AttachDevComm返回值
CLIENT_NET_API BOOL CALL_METHOD CLIENT_DetachDevComm(LLONG lAttachHandle);

// 上海巴士设备控制接口，包括控制PAD关机和重启等
CLIENT_NET_API BOOL CALL_METHOD CLIENT_ControlSpecialDevice(LLONG lLoginID, NET_SPECIAL_CTRL_TYPE emType, void* pInBuf, void* pOutBuf = NULL, int nWaitTime = NET_INTERFACE_DEFAULT_TIMEOUT);

//获取HCDZ采集信息
CLIENT_NET_API BOOL  CALL_METHOD CLIENT_GetHCDZInfo(LLONG lLoginID, const NET_IN_HCDZ_LIST_INFO* pInParam, NET_OUT_HCDZ_LIST_INFO* pOutParam, int nWaitTime = 3000);

//获取HCDZ能力集
CLIENT_NET_API BOOL  CALL_METHOD CLIENT_GetHCDZCaps(LLONG lLoginID, const NET_IN_HCDZ_CAPS* pInParam, NET_OUT_HCDZ_CAPS* pOutParam, int nWaitTime = 3000);


// 设置云台持续性控制命令发送间隔，该设置对当前所有登录的云台设备都生效（单位ms，间隔时间需大于100ms，否则不生效）
CLIENT_NET_API void CALL_METHOD CLIENT_PTZCmdSendIntervalTime(DWORD dwIntervalTime);

/**********************************************************************************
功能描述:获取HADT(山东金鲁班宏安电梯)运行状态
参数定义:
    lLoginID:登录接口返回的句柄
    pInBuf  :输入参数,需初始化dwSize
    pOutBuf :输出参数,需初始化dwSize
    nWaitTime :接口超时时间
返 回 值:	BOOL  TRUE :成功; FALSE :失败
**********************************************************************************/
CLIENT_NET_API BOOL CALL_METHOD CLIENT_GetHADTStatus(LLONG lLoginID, const NET_IN_HADT_STATUS* pInBuf, NET_OUT_HADT_STATUS* pOutBuf,int nWaitTime = 3000);

/**********************************************************************************
功能描述:控制报警输出（车载定制）
参数定义:
    lLoginID:登录接口返回的句柄
    pInBuf  :输入参数,需初始化dwSize
    pOutBuf :输出参数,需初始化dwSize
    nWaitTime :接口超时时间
返 回 值:	BOOL  TRUE :成功; FALSE :失败
**********************************************************************************/
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetAlarmOut(LLONG lLoginID, const NET_IN_SET_ALARMOUT* pInBuf, NET_OUT_SET_ALARMOUT* pOutBuf,int nWaitTime);

//开启EVS定时录像
CLIENT_NET_API BOOL CALL_METHOD CLIENT_StartLinkRecord(LLONG lLoginID, const NET_IN_LINK_RECORD_CTRL *pstIn, NET_OUT_LINK_RECORD_CTRL *pstOut, int nWaitTime);

// 北京公交定制接口，传入Ukey值
/**********************************************************************************
功能描述:设备此次登陆的Ukey值
参数定义:
    lLoginID:登录接口返回的句柄
    pInBuf  :输入参数,需初始化dwSize
    pOutBuf :输出参数,需初始化dwSize
    nWaitTime :接口超时时间
返 回 值:	BOOL  TRUE :成功; FALSE :失败
**********************************************************************************/
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetDeviceUkey(LLONG lLoginID, const NET_IN_SET_UEKY *pInBuf, NET_OUT_SET_UEKY *pOutBuf, int nWaitTime);

typedef struct tagNET_IN_NETACCESS
{
	DWORD		dwSize;									// 结构体大小
	char		szMac[DH_MACADDR_LEN];					// 设备mac地址
	char		szSecurity[MAX_SECURITY_CODE_LEN];		// 安全码
	BYTE		byInitStaus;							// 设备初始化状态：搜索设备接口(CLIENT_SearchDevices、CLIENT_StartSearchDevices的回调函数、CLIENT_SearchDevicesByIPs)返回字段byInitStatus的值
	BYTE		byReserved[3];							// 保留字段
}NET_IN_NETACCESS;
typedef struct tagNET_OUT_NETACCESS
{
	DWORD		dwSize;					// 结构体大小
}NET_OUT_NETACCESS;
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetNetAccess(const NET_IN_NETACCESS* pNetAccessIn, NET_OUT_NETACCESS* pNetAccessOut, DWORD dwWaitTime, char* szLocalIp);

// 对应CLIENT_StartSearchCustomDevices接口
// 搜索OEM设备类型枚举
typedef enum tagEM_SEARCH_OEM_DEVICE_TYPE
{
	EM_TYPE_JIANGSU_CHUANGTONG = 0,    // 江苏创通OEM设备类型
	EM_TYPE_MAX,					   // 最大枚举值
}EM_SEARCH_OEM_DEVICE_TYPE;

// OEM设备信息
typedef struct tagCUSTOM_DEVICE_NETINFO
{
	char                szMac[DH_MACADDR_LEN];                  // MAC地址,如00:40:9D:31:A9:0A
	char                szIP[DH_MAX_IPADDR_EX_LEN];				// IP地址,如10.0.0.231
	char                szDevName[DH_MACHINE_NAME_NUM];         // 设备名称,固定为Wireless Transmission Device
	BYTE				byReserved[1024];						// 保留字节
}CUSTOM_DEVICE_NETINFO;

// 异步搜索OEM设备回调（pCustomDevNetInf内存由SDK内部申请释放）
typedef void (CALLBACK *fSearchCustomDevicesCB)(CUSTOM_DEVICE_NETINFO *pCustomDevNetInfo, void* pUserData);

// CLIENT_StartSearchCustomDevices接口的输入参数
typedef struct tagNET_IN_SEARCH_PARAM 
{
	DWORD							dwSize;                  // 结构体大小
	fSearchCustomDevicesCB			cbFunc;			         // 搜索OEM设备回调函数
	void*							pUserData;               // 用户传入的自定义数据
	char*							szLocalIp;				 // 本地IP
	EM_SEARCH_OEM_DEVICE_TYPE       emSearchOemDeviceType;   //	搜索OEM设备类型
}NET_IN_SEARCH_PARAM;

// CLIENT_StartSearchCustomDevices的输出参数
typedef struct tagNET_OUT_SEARCH_PARAM
{
	DWORD		dwSize;
}NET_OUT_SEARCH_PARAM;

// 异步组播搜索OEM设备, (pInParam, pOutParam内存由用户申请释放),不支持多线程调用,配件产品线需求
CLIENT_NET_API LLONG CALL_METHOD CLIENT_StartSearchCustomDevices(const NET_IN_SEARCH_PARAM *pInParam, NET_OUT_SEARCH_PARAM *pOutParam); 
// 停止组播搜索OEM设备
CLIENT_NET_API BOOL CALL_METHOD CLIENT_StopSearchCustomDevices(LLONG lSearchHandle);

// 设备登录策略入参
typedef struct tagNET_IN_LOGIN_POLICY_PARAM
{
	DWORD               dwSize;
	int		            nDevicePort;							// 设备端口号
	char		        *szDeviceIp;			                // 设备ip地址    
	char		        *szUserName;		                    // 用户名
	char 		        *szPassword;		                    // 用户密码

	EM_LOGIN_SPAC_CAP_TYPE 		emSpecCap;				        // 登陆类型, 目前仅支持 TCP / Mobile / P2P 登录
	void	            *pCapParam; 							// 登陆附带参数, 具体类型与emSpeCap相关

	int                 nLoginPolicyFlag;                       // 登录策略标志位
	// bit0 == 1 快速登录: 设备信息 序列号/报警输入/输出参数无效 

	int                 nPlayPolicyFlag;                        // 实时预览策略标志位
	// bit0 == 1 不支持画中画

	int                 nPlayBackPolicyFlag;					// 录像回放和录像查询策略标志位
	// bit0 == 1 不查询画中画能力

}NET_IN_LOGIN_POLICY_PARAM;

// 设备登录策略出参
typedef struct tagNET_OUT_LOGIN_POLICY_PARAM
{
	DWORD               dwSize;
	NET_DEVICEINFO_Ex   stuDeviceInfo;                          // 设备信息
}NET_OUT_LOGIN_POLICY_PARAM;


// 登录扩展接口, 支持策略
CLIENT_NET_API LLONG CALL_METHOD CLIENT_LoginWithPolicy(const NET_IN_LOGIN_POLICY_PARAM* pstInParam, NET_OUT_LOGIN_POLICY_PARAM* pstOutParam, int nWaitTime);

// 本地优化模式
typedef enum __EM_LOCAL_MODE
{
	EM_LOCAL_PLAY_FLAG_MODE = 101,      // 实时预览策略标志位  bit0 == 1 不支持画中画  bit1 == 1 不支持通道信息校验 
	EM_LOCAL_PLAYBACK_FLAG_MODE = 102,  // 录像回放和录像查询策略标志位  bit0 == 1 不支持画中画
} EM_LOCAL_MODE;

// 设置本地一些特殊的优化模式
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetLocalMode(LLONG lLoginID, EM_LOCAL_MODE emType, void* pValue);


// CLIENT_TriggerAutoInspection 接口入参
typedef struct tagNET_IN_TRIGGER_AUTO_INSPECTION
{
	DWORD dwSize;
}NET_IN_TRIGGER_AUTO_INSPECTION;

// CLIENT_TriggerAutoInspection 接口出参
typedef struct tagNET_OUT_TRIGGER_AUTO_INSPECTON
{
	DWORD dwSize;
}NET_OUT_TRIGGER_AUTO_INSPECTON;

// 触发设备自检（楼宇产品线专用需求）
CLIENT_NET_API BOOL CALL_METHOD CLIENT_TriggerAutoInspection(LLONG lLoginID, const NET_IN_TRIGGER_AUTO_INSPECTION* pstInParam, NET_OUT_TRIGGER_AUTO_INSPECTON* pstOutParam, int nWaitTime);

// CLIENT_GetLicenseAssistInfo 接口入参
typedef struct tagNET_IN_GET_LICENSE_INFO
{
	DWORD dwSize;								// 赋值为结构体大小
}NET_IN_GET_LICENSE_INFO;

// 需要被License限制的库信息
typedef struct tagNET_RESTRICTED_LIB_INFO
{
	char szId[40];								// 被限制库Id
	char szVersion[32];							// 被限制库的版本
	char szKey1[128];							// 所需要的特定信息1，具体内容由限制库确定
	char szKey2[128];							// 所需要的特定信息2，具体内容由限制库确定
	char szKey3[128];							// 所需要的特定信息3，具体内容由限制库确定
	char szKey4[128];							// 所需要的特定信息4，具体内容由限制库确定
	char szReserved[1024];						// 保留字段
}NET_RESTRICTED_LIB_INFO;

// CLIENT_GetLicenseAssistInfo 接口出参
typedef struct tagNET_OUT_GET_LICENSE_INFO
{
	DWORD dwSize;								// 赋值为结构体大小
	char  szSeriesNum[32];						// 设备序列号
	char  szMac[8][32];							// 设备Mac 地址
	int   nMacRet;								// 返回的Mac地址数量
	char  szBindInfo[256];						// 绑定信息
	char  szAppVersion[32];						// 应用程序版本
	char  szAppVerificationCode[512];			// 应用程序校验信息	
	char  szLicenseLibVsersion[32];				// License 管理库版本信息
	NET_RESTRICTED_LIB_INFO stuLibInfo[8];		// 需要被License限制的库信息
	int	  nLibInfoRet;							// 返回的stuLibInfo结构体数量
}NET_OUT_GET_LICENSE_INFO;

// 获取制作License的辅助信息
CLIENT_NET_API BOOL CALL_METHOD CLIENT_GetLicenseAssistInfo(LLONG lLoginID, const NET_IN_GET_LICENSE_INFO* pstInParam, NET_OUT_GET_LICENSE_INFO* pstOutParam, int nWaitTime);

// CLIENT_SetLicense 接口入参
typedef struct tagNET_IN_SET_LICENSE
{
	DWORD dwSize;								// 赋值为结构体大小
	char  szLicenseInfo[8192];					// License 数据
	char  szSignature[512];						// License 数据的数字签名
}NET_IN_SET_LICENSE;

// CLIENT_SetLicense 接口出参
typedef struct tagNET_OUT_SET_LICENSE
{
	DWORD dwSize;								// 赋值为结构体大小
}NET_OUT_SET_LICENSE;

// 设置License
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetLicense(LLONG lLoginID, const NET_IN_SET_LICENSE* pstInParam, NET_OUT_SET_LICENSE* pstOutParam, int nWaitTime);

// 获取设备状态入参
typedef struct tagNET_IN_UNIFIEDINFOCOLLECT_GET_DEVSTATUS
{
    DWORD               dwSize;                                 // 结构体大小
}NET_IN_UNIFIEDINFOCOLLECT_GET_DEVSTATUS;

// 供电类型
typedef enum tagNET_EM_POWER_TYPE
{
    NET_EM_POWER_TYPE_UNKNOWN = -1,                     // 未知              
    NET_EM_POWER_TYPE_POWERADAPTER,                     // 电源适配器
    NET_EM_POWER_TYPE_BATTERY,                          // 电池
    NET_EM_POWER_TYPE_BATTERY_AND_POWERADAPTER,         // 电池+电源适配器
}NET_EM_POWER_TYPE;

// 电源电池相关信息
typedef struct tagNET_DEVSTATUS_POWER_INFO
{
	UINT                nBatteryPercent;                        // 电池电量百分比,0~100
    NET_EM_POWER_TYPE   emPowerType;                            // 供电类型
}NET_DEVSTATUS_POWER_INFO;

// 有线网连接状态
typedef enum tagNET_EM_ETH_STATE
{
    NET_EM_ETH_UNKNOWN,                                         // 未知
    NET_EM_ETH_CONNECT,                                         // 连接
    NET_EM_ETH_DISCONNECT,                                      // 未连接
}NET_EM_ETH_STATE;

// 网络相关信息
typedef struct tagNET_DEVSTATUS_NET_INFO
{
    UINT                nWifiIntensity;                         // wifi信号强度等级，0~5，0表示没有信号
    UINT                nWifiSignal;                            // wifi信号强度，单位dbm, 0~100,0表示没有信号
    UINT                nCellulSignal;                          // 2g/3g/4g信号强度,单位dbm. 0~100, 0表示没有信号
    UINT                nCellulIntensity;                       // 2g/3g/4g信号强度等级,0~5, 0表示没有信号
    NET_EM_ETH_STATE    emEthState;                             // 有线网连接状态
    UINT                n3Gflux;                                // 蜂窝网络实际使用流量，单位：MB
    UINT                n3GfluxByTime;                          // 网络实际使用时长，单位：分钟     
}NET_DEVSTATUS_NET_INFO;

// 主机防拆状态
typedef enum tagNET_EM_TAMPER_STATE
{
    NET_EM_TAMPER_UNKNOWN = -1,                             // 未知 
    NET_EM_TAMPER_NOALARM,                                  // 未报警
    NET_EM_TAMPER_ALARMING,                                 // 报警中
}NET_EM_TAMPER_STATE;

// 获取设备状态出参
typedef struct tagNET_OUT_UNIFIEDINFOCOLLECT_GET_DEVSTATUS
{
    DWORD                           dwSize;                         // 结构体大小
    NET_DEVSTATUS_POWER_INFO        stuPowerInfo;                   // 电源电池相关信息
    NET_DEVSTATUS_NET_INFO          stuNetInfo;                     // 网络相关信息
    char                            szVersion[DH_COMMON_STRING_32]; // 主机软件版本
    NET_EM_TAMPER_STATE             emTamperState;                  // 主机防拆状态
}NET_OUT_UNIFIEDINFOCOLLECT_GET_DEVSTATUS;

// 获取设备状态, DMSS专用接口, pInParam与pOutParam内存由用户申请释放
CLIENT_NET_API BOOL CALL_METHOD CLIENT_GetUnifiedStatus(LLONG lLoginID, NET_IN_UNIFIEDINFOCOLLECT_GET_DEVSTATUS* pInParam, NET_OUT_UNIFIEDINFOCOLLECT_GET_DEVSTATUS* pOutParam, int nWaitTime);

// CLIENT_QueryUserRights 接口输入参数
typedef struct tagNET_IN_QUERYUSER_RIGHT
{
	DWORD				dwSize; 					// 此结构体大小			
} NET_IN_QUERYUSER_RIGHT;

// CLIENT_QueryUserRights 接口输入参数
typedef struct tagNET_OUT_QUERYUSER_RIGHT
{
	DWORD				dwSize; 					// 此结构体大小		
	DWORD				dwRightNum; 				// 权限信息
	OPR_RIGHT_NEW		rightList[DH_NEW_MAX_RIGHT_NUM];					  
	USER_INFO_NEW		userInfo;					// 用户信息
	DWORD				dwFunctionMask; 			// 掩码；0x00000001 - 支持用户复用，0x00000002 - 密码修改需要校验
} NET_OUT_QUERYUSER_RIGHT;

// APP用户操作优化接口
CLIENT_NET_API BOOL CALL_METHOD CLIENT_QueryUserRights(LLONG lLoginID, const NET_IN_QUERYUSER_RIGHT* pstInParam, NET_OUT_QUERYUSER_RIGHT* pstOutParam ,int waittime);

#ifdef __cplusplus
}
#endif



#endif // DHNETSDKEX_H



