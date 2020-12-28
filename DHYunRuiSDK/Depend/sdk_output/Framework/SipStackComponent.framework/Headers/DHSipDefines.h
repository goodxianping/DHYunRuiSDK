//
//  DHSipDefines.h
//  PlayerComponent
//
//  Copyright (c) 2015年. All rights reserved.
//

#ifndef _DHSipDefines_h
#define _DHSipDefines_h

const char LOG_TAG_MANAGER[] = "Sip_Stack";

struct LiveStreamInfo
{
    char deviceIP[20];   //设备IP（sip服务器地址）
    //char deviceID[20];   //设备ID
    char deviceID[50];   //设备ID 15+1+32
    
    char recvStreamIP[20];  //本地IP地址
    unsigned int recvAudioStreamPort; //本地音频接收端口
    unsigned int recvVideoStreamPort; //本地视频接收端口
    
    char sendStreamIP[20];  //设备端IP地址
    unsigned int sendAudioStreamPort; //设备端音频接收端口
    unsigned int sendVideoStreamPort; //设备端视频接收端口
    
    unsigned int sipPort; //sip服务器端口
    char videoSDPContent[1024]; //从设备呼叫sdp中解析出的video信息
    char audioSDPContent[1024]; //从设备呼叫sdp中解析出的audio信息
    
    int encodeType; //音频编码类型
    int sampleRate; //音频采样率
    int sampleDepth; //音频采样深度
    int packType; //打包方式
    
    int cid; //call ID
    int did; //dialog ID
    int tid; //transaction ID
    
    char strContentType[100];
    char rspSDPContent[1024]; //发送消息时携带的sdp（自己拼接组装）
    char reqSDPContent[1024]; //设备呼叫时，携带的sdp信息
    
    char videoOutSDPContent[1024]; //发送消息时携带的video sdp，暂时废弃
    char audioOutSDPContent[1024]; //发送消息时携带的audio sdp，暂时废弃

    char pai[256]; //PAI（P-Asserted-Identity）头字段
    
    char userAgent[256];
};
#endif
