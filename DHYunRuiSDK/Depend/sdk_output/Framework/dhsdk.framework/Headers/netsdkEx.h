/*
* Copyright (c) 2009, �㽭�󻪼����ɷ����޹�˾
* All rights reserved.
*
* ժ��Ҫ��SDK�ӿںܶ�,���ƻ�һЩ�����õĹ��ܿ��Է���dhnetsdkEx.h,
*         �����ṩ dhnetsdk.h,
*         ������Ŀ�����ṩ dhnetsdkEx.h
*/
//////////////////////////////////////////////////////////////////////////
#ifndef DHNETSDKEX_H
#define DHNETSDKEX_H

#include "netsdk.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 ** ��������
 ***********************************************************************/

/************************************************************************
 ** ö�ٶ���
 ***********************************************************************/

/************************************************************************
 ** �ṹ�嶨��
************************************************************************/

 //////////////////////////////////////͸����չ�ӿڲ���//////////////////////////////////////////////////////////////////
 
 // ͸������
 typedef enum   tagNET_TRANSMIT_INFO_TYPE
 {
    NET_TRANSMIT_INFO_TYPE_DEFAULT,                 // Ĭ�����ͣ���CLIENT_TransmitInfoForWeb�ӿڵļ���͸����ʽ
    NET_TRANSMIT_INFO_TYPE_F6,                      // F6��͸��
 } NET_TRANSMIT_INFO_TYPE;

 // CLIENT_TransmitInfoForWebEx�������
 typedef struct tagNET_IN_TRANSMIT_INFO
 {
    DWORD                   dwSize;                         // �û�ʹ�øýṹ�壬dwSize�踳ֵΪsizeof(NET_IN_TRANSMIT_INFO)
    NET_TRANSMIT_INFO_TYPE  emType;                         // ͸������
    char*                   szInJsonBuffer;                 // Json��������,�û�����ռ�
    DWORD                   dwInJsonBufferSize;             // Json�������ݳ���
    unsigned char*          szInBinBuffer;                  // �������������ݣ��û�����ռ�
    DWORD                   dwInBinBufferSize;              // �������������ݳ���
 } NET_IN_TRANSMIT_INFO;

 // CLIENT_TransmitInfoForWebEx�������
 typedef struct tagNET_OUT_TRANSMIT_INFO
 {
    DWORD                   dwSize;                         // �û�ʹ�øýṹ��ʱ��dwSize�踳ֵΪsizeof(NET_OUT_TRANSMIT_INFO)
    char*                   szOutBuffer;                    // Ӧ�����ݻ���ռ�, �û�����ռ�
    DWORD                   dwOutBufferSize;                // Ӧ�����ݻ���ռ䳤��
    DWORD                   dwOutJsonLen;                   // JsonӦ�����ݳ���
    DWORD                   dwOutBinLen;                    // ������Ӧ�����ݳ���
 } NET_OUT_TRANSMIT_INFO;

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////�첽��͸���ṹ�嶨�忪ʼ////////////////////////////////////////////////////////////////////////////////////////////
 // CLIENT_AttachTransmitInfo �ϱ���Ϣ�ص�
 typedef struct tagNET_CB_TRANSMIT_INFO
 {
     BYTE*              pBuffer;            // ���ݻ����ַ��SDK�ڲ�����ռ�
     DWORD              dwBufferSize;       // ���ݻ����ܳ���
     DWORD              dwJsonLen;          // Json���ݳ���
     DWORD              dwBinLen;           // ���������ݳ���
     BYTE               byReserved[512];    // �����ֽ�
 } NET_CB_TRANSMIT_INFO;

 // CLIENT_AttachTransmitInfo()�ص�����ԭ�ͣ���һ������lAttachHandle��CLIENT_AttachTransmitInfo����ֵ
 typedef int  (CALLBACK *AsyncTransmitInfoCallBack)(LLONG lAttachHandle, NET_CB_TRANSMIT_INFO* pTransmitInfo, LDWORD dwUser);

 // CLIENT_AttachTransmitInfo�������
 typedef struct tagNET_IN_ATTACH_TRANSMIT_INFO
 {
     DWORD                       dwSize;                         // �û�ʹ�øýṹ��ʱ��dwSize�踳ֵΪsizeof(NET_IN_ATTACH_TRANSMIT_INFO)
     AsyncTransmitInfoCallBack   cbTransmitInfo;                 // �ص�����
     LDWORD				         dwUser;                         // �û�����
     char*                       szInJsonBuffer;                 // Json��������,�û�����ռ�
     DWORD                       dwInJsonBufferSize;             // Json�������ݳ���  `

 }NET_IN_ATTACH_TRANSMIT_INFO;

 // CLIENT_AttachTransmitInfo�������
 typedef struct tagNET_OUT_ATTACH_TRANSMIT_INFO
 {
     DWORD                   dwSize;                         // �û�ʹ�øýṹ��ʱ��dwSize�踳ֵΪsizeof(NET_OUT_ATTACH_TRANSMIT_INFO)
     BYTE*                   szOutBuffer;                    // Ӧ�𻺳��ַ,�û�����ռ�
     DWORD                   dwOutBufferSize;                // Ӧ�𻺳��ܳ���
     DWORD                   dwOutJsonLen;                   // Ӧ��Json���ݳ���
     DWORD                   dwOutBinLen;                    // Ӧ����������ݳ��� 
 } NET_OUT_ATTACH_TRANSMIT_INFO;

 // CLIENT_DetachTransmitInfo�������
 typedef struct tagNET_IN_DETACH_TRANSMIT_INFO
 {
     DWORD                   dwSize;                         // �û�ʹ�øýṹ��ʱ��dwSize�踳ֵΪsizeof(NET_IN_DETACH_TRANSMIT_INFO)
     char*                   szInJsonBuffer;                 // Json��������,�û�����ռ�
     DWORD                   dwInJsonBufferSize;             // Json�������ݳ���
 } NET_IN_DETACH_TRANSMIT_INFO;

 // CLIENT_DetachTransmitInfo�������
 typedef struct tagNET_OUT_DETACH_TRANSMIT_INFO
 {
     DWORD                   dwSize;                         // �û�ʹ�øýṹ��ʱ��dwSize�踳ֵΪsizeof(NET_OUT_DETACH_TRANSMIT_INFO)
     char*                   szOutBuffer;                    // Ӧ�����ݻ���ռ�, �û�����ռ�
     DWORD                   dwOutBufferSize;                // Ӧ�����ݻ���ռ䳤��
     DWORD                   dwOutJsonLen;                   // Ӧ��Json���ݳ���
 } NET_OUT_DETACH_TRANSMIT_INFO;

//////�Ϻ�BUS//////
 
// �Ϻ���ʿ�������ͣ� ��ӦCLIENT_ControlSpecialDevice�ӿ�
typedef enum tagNET_SPECIAL_CTRL_TYPE
{
    NET_SPECIAL_CTRL_SHUTDOWN_PAD,            // �ر�PAD����, pInBuf��Ӧ����NET_IN_SHUTDOWN_PAD*, pOutBuf��Ӧ����NET_OUT_SHUTDOWN_PAD*
    NET_SPECIAL_CTRL_REBOOT_PAD,              // ����PAD����, pInBuf��Ӧ����NET_IN_REBOOT_PAD*, pOutBuf��Ӧ����NET_OUT_REBOOT_PAD*                 
} NET_SPECIAL_CTRL_TYPE;

 //////////////////////////////////////////////�豸�������ýṹ�嶨�忪ʼ////////////////////////////////////////////////////////////////////////////////////////////
 // CLIENT_DevSpecialCtrl �����������
 typedef enum tagEM_DEV_SPECIAL_CTRL_TYPE
 {
     DEV_SPECIAL_CTRL_TYPE_RECORD_FLUSH,                  // ����¼������ǿ��д��Ӳ��, pInBuf=NET_IN_RECORD_FLUSH_INFO* , pOutBuf=NET_OUT_RECORD_FLUSH_INFO*
 } EM_DEV_SPECIAL_CTRL_TYPE;
 
 // CLIENT_DevSpecialCtrl, ��Ӧ DEV_SPECIAL_CTRL_TYPE_RECORD_FLUSH �������
 typedef struct tagNET_IN_NET_IN_RECORD_FLUSH_INFO
 {
    DWORD                                      dwSize;       // �û�ʹ�øýṹ��ʱ��dwSize�踳ֵΪsizeof(NET_IN_RECORD_FLUSH_INFO)               
    int                                        nChannel;     // ͨ����
    NET_STREAM_TYPE                            emStreamType; // ��������, ��Ч���� "main", "Extra1", "Extra2", "Extar3", "Snapshot"     
 }NET_IN_RECORD_FLUSH_INFO;

 // CLIENT_DevSpecialCtrl, ��Ӧ DEV_SPECIAL_CTRL_TYPE_RECORD_FLUSH �������
 typedef struct tagNET_OUT_RECORD_FLUSH_INFO
 {
     DWORD                                     dwSize;       // �û�ʹ�øýṹ��ʱ��dwSize�踳ֵΪsizeof(NET_OUT_RECORD_FLUSH_INFO)              
 }NET_OUT_RECORD_FLUSH_INFO;
 
 //////////////////////////////////////////////�豸�������ýṹ�嶨�����////////////////////////////////////////////////////////////////////////////////////////////
 

typedef struct tagNET_IN_REBOOT_PAD
{
    DWORD               dwSize;                  // �û�ʹ�øýṹ��ʱ��dwSize �踳ֵΪ sizeof(NET_IN_REBOOT_PAD)
} NET_IN_REBOOT_PAD;

typedef struct tagNET_OUT_REBOOT_PADE
{
    DWORD               dwSize;                  // �û�ʹ�øýṹ��ʱ��dwSize �踳ֵΪ sizeof(NET_OUT_REBOOT_PAD)
} NET_OUT_REBOOT_PAD;

typedef struct tagNET_IN_SHUTDOWN_PAD
{
    DWORD               dwSize;                  // �û�ʹ�øýṹ��ʱ��dwSize �踳ֵΪ sizeof(NET_IN_REBOOT_PAD)
    int                 nDelayTime;              // ��ʱ�ػ�ʱ��, ��λ����
} NET_IN_SHUTDOWN_PAD;

typedef struct tagNET_OUT_SHUTDOWN_PAD
{
    DWORD               dwSize;                  // �û�ʹ�øýṹ��ʱ��dwSize �踳ֵΪ sizeof(NET_OUT_SHUTDOWN_PAD)
} NET_OUT_SHUTDOWN_PAD;

//////////////////////////////////////////////�첽��͸���ṹ�嶨�����////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////�豸������Ϣ�ṹ�嶨�忪ʼ ////////////////////////////////////////////////////////////////////////////////////////////

typedef struct tagNET_DHDEV_ETHERNET_INFO
{
    DWORD               dwSize;                                 // �û�ʹ�øýṹ��ʱ��dwSize �踳ֵΪ sizeof(NET_DHDEV_ETHERNET_INFO)
    int                 nEtherNetNum;                           // ��̫������
    DH_ETHERNET_EX      stuEtherNet[DH_MAX_ETHERNET_NUM_EX];    // ��̫����
} NET_DHDEV_ETHERNET_INFO;

//////////////////////////////////////////////�豸������Ϣ�ṹ�嶨�����////////////////////////////////////////////////////////////////////////////////////////////


//��ȡHCDZ�ɼ���Ϣ,�������
typedef struct tagNET_IN_HCDZ_LIST_INFO 
{
    DWORD                           dwSize;							//  �ṹ���С, �����߱����ʼ�����ֶ�
	UINT							nIndexNum;					   //����szindex��Ч����
    UINT                            szIndex[DH_COMMON_STRING_64]; //һ������,index ֵ��ͨ���±��Ӧ
}NET_IN_HCDZ_LIST_INFO;

// HCDZ�ɼ���Ϣ�����ģ��ɼ���Ϣ
typedef struct tagNET_HCDZ_INFO 
{
    UINT            nChannelID;								// ͨ����(��0��ʼ)
    UINT            nAIMode;								// AI��������ģʽ����  0 ��ʾ��������0-10000��Ӧ0-100%���� 1 ��ʾ4-20mA������ʽ����������0-10000��Ӧ4-20mA(20%-100%AI����)
	UINT            nAIO;									// ���ģ��ģ������ͨ������ 20��ʾ20mA 5��ʾ5V 10��ʾ10V
	UINT			nAnalogInputNum;						// ��Ч��ģ������������
    UINT            arrAnalogInput[DH_COMMON_STRING_8];     // ��һ������,���ģ��ģ��������Ĵ���ֵ �޷�����0-10000��Ӧ0-�����̣�ʵ��ֵ=DATA/10000*����AI0����λmA��V 
	UINT			nDINum;						            // ��Ч��ģģ�鿪������������
    UINT            arrDI[DH_COMMON_STRING_4];              // ���ģ�鿪��������ֵ����һ�����飬0Ϊ�أ�1Ϊ��
	UINT			nDONum;						            // ��Ч��ģ�鿪�����������
    UINT            arrDO[DH_COMMON_STRING_4];              // ���ģ�鿪�������ֵ����һ�����飬0Ϊ�أ�1Ϊ��
}NET_HCDZ_INFO;

// ��ȡHCDZ�ɼ���Ϣ,�������
typedef struct tagNET_OUT_HCDZ_LIST_INFO 
{
    DWORD                       dwSize;                             // �ṹ���С, �����߱����ʼ�����ֶ�
	UINT				        nValidNum;						    // ����stuInfo����Ч����
    NET_HCDZ_INFO				stuInfo[DH_COMMON_STRING_64];       // HCDZ�ɼ���Ϣ
}NET_OUT_HCDZ_LIST_INFO;

typedef struct tagNET_IN_HCDZ_CAPS 
{
    DWORD                           dwSize;                          // �ṹ���С, �����߱����ʼ�����ֶ�
}NET_IN_HCDZ_CAPS;

// ��ȡHCDZ(�ݲ����)�����ṹ��
typedef struct tagCFG_HCDZ_CAPS
{
	DWORD                               dwSize;                                 // �ṹ���С, �����߱����ʼ�����ֶ�
	char								szModelID[DH_COMMON_STRING_32];		    // �豸�ͺ�
	unsigned int						nVersion;								// �汾
	unsigned int						nAnalogsNum;							// ���ģ��ģ�����������
	unsigned int						nDINum;									// ���ģ�鿪�����������
	unsigned int						nDONum;									// ���ģ�鿪�����������
}NET_OUT_HCDZ_CAPS;

// ��ȡ����״̬(HADTɽ����³��갲����),�������
typedef struct tagNET_IN_HADT_STATUS
{
    DWORD                               dwSize;                                 // �ṹ���С, �����߱����ʼ�����ֶ�
}NET_IN_HADT_STATUS;

// ��ȡ����״̬(HADTɽ����³��갲����),�������
typedef struct tagNET_OUT_HADT_STATUS
{
    DWORD                               dwSize;                                 // �ṹ���С, �����߱����ʼ�����ֶ�
    int                                 nLevelSignal1;                          // ¥���ź�ֵ�����ڻ�ȡ¥��ĸ�λ����Ϣ����Χ(0~37)�ɿͻ���ȡֵ�����н���
    int                                 nLevelSignal2;                          // ¥���ź�ֵ�����ڻ�ȡ¥���ʮλ����Ϣ����Χ(0~37)�ɿͻ���ȡֵ�����н���
    int                                 nLevelSignal3;                          // ¥���ź�ֵ�����ڻ�ȡ¥��İ�λ����Ϣ����Χ(0~37)�ɿͻ���ȡֵ�����н��� 
    DWORD                               dwliftStatus;                           // ����״̬��Ϣ��ÿһλ����һ��״̬
                                                                                // bit0: ���𣻸�λ��1��ʾ������0��ʾû�е���
                                                                                // bit1: �Ծȣ���λ��1��ʾ�Ծȣ���0��ʾû���Ծ�
                                                                                // bit2: ���أ���λ��1��bit3��bit12��0��ʾ���أ�������ʾ��Ч
                                                                                // bit3: ���أ���λ��1��bit2��bit12��0��ʾ���أ�������ʾ��Ч
                                                                                // bit4: ��������λ��1��ʾ��������0��ʾû������
                                                                                // bit5: ���ޣ���λ��1��ʾ���ޣ���0��ʾû�м���
                                                                                // bit6: ���У���λ��1��bit7��0���У�������ʾ��Ч
                                                                                // bit7: ���У���λ��1��bit6��0��ʾ���У�������ʾ��Ч
                                                                                // bit8: ������վ����λ��1��ʾ��������վ����0��ʾû��������վ
                                                                                // bit12: ���أ���λ��1��bit2��bit3��0��ʾ���أ�������ʾ��Ч
                                                                                // bit13: ֹͣ/���У���λ��1��ʾ���У���0��ʾֹͣ
                                                                                // bit14: ���ţ���λ��1��bit15��0��ʾ���ţ�������ʾ��Ч
                                                                                // bit15: ���ţ���λ��1��bit14��0��ʾ���ţ�������ʾ��Ч
}NET_OUT_HADT_STATUS;

//����������ƽӿ�CLIENT_SetAlarmOut���������
typedef struct tagNET_IN_SET_ALARMOUT
{
    DWORD                               dwSize;                                 // �ṹ���С����Ҫ��ֵ
    int                                 nChannel;                               // ͨ���ţ���0��ʼ
    int                                 nTime;                                  // time > 0 ʱ, time��Ч����λ:��
    int                                 nLevel;                                 // time = 0 ʱ, level��Ч��time��level��Ϊ0ʱ����ʾֹͣ
}NET_IN_SET_ALARMOUT;

//����������ƽӿ�CLIENT_SetAlarmOut���������
typedef struct tagNET_OUT_SET_ALARMOUT
{   
    DWORD                               dwSize;                                 // �ṹ���С,��Ҫ��ֵ
}NET_OUT_SET_ALARMOUT;

// ¼������
typedef enum tagEM_NET_LINK_RECORD_EVENT
{
    EM_NET_LINK_RECORD_UNKNOWN,                         // δ֪
    EM_NET_LINK_RECORD_ALARM,                           // Alarm
} EM_NET_LINK_RECORD_EVENT;

//CLIENT_StartLinkRecord�������
typedef struct tagNET_IN_LINK_RECORD_CTRL
{
    DWORD                       dwSize;                 // �ýṹ���С
    unsigned int                nChannel;               // ͨ����
    unsigned int                nLength;                // ¼��ʱ��
    EM_NET_LINK_RECORD_EVENT    emType;                 // ¼������"Alarm"-����¼�񣬵�ǰ��֧������¼��
} NET_IN_LINK_RECORD_CTRL;

//CLIENT_StartLinkRecord�������
typedef struct tagNET_OUT_LINK_RECORD_CTRL
{
    DWORD                       dwSize;                 // �ýṹ���С
} NET_OUT_LINK_RECORD_CTRL;

// CLIENT_SetDeviceUkey�������
typedef struct tagNET_IN_SET_UEKY
{
    DWORD                       dwSize;                 // �ýṹ���С
    char                        szUkey[128];             // Ukey��
}NET_IN_SET_UEKY;

// CLIENT_SetDeviceUkey �������
typedef struct tagNET_OUT_SET_UEKY
{
    DWORD                       dwSize;                 // �ýṹ���С
}NET_OUT_SET_UEKY;
/***********************************************************************
 ** �ص���������
 ***********************************************************************/

 /**************************************************************************************
 *   Funcname: fAsynPlayHandleCallBack
 *   Purpose:  �첽ʵʱ���ӻص�����
 *   InputParam:    LLONG                    :lPlayHandle // ʵʱ���Ӳ��ž��
 *   InputParam:    LLONG                    :lLoginID    // ��½���
 *   InputParam:    int                      :nChannelID  // ͨ����
 *   InputParam:    HWND                     :hWnd        // ���ھ��
 *   InputParam:    LDWORD                   :dwUser      // �û�
 *   Created:%2015%:%12%:%23%  
 *   Revision Record:date:author:modify sth
**************************************************************************************/
typedef void (CALLBACK *fAsynPlayHandleCallBack)(LLONG lPlayHandle, LLONG lLoginID, int nChannelID, HWND hWnd, LDWORD dwUser);




/************************************************************************
 ** �ӿڶ���
 ***********************************************************************/

/******************************************************************************
��������	:	����¼���ļ�--��չ,�ɼ�������ת����
�������	:	
    lLoginID:       ��¼�ӿڷ��صľ��
    lpRecordFile:   ��ѯ¼��ӿڷ��ص�¼����Ϣ
    sSavedFileName: ����¼���ļ���,֧��ȫ·��
    cbDownLoadPos:  ���ؽ��Ȼص�����(�ص����ؽ���,���ؽ��)
    dwUserData:     ���ؽ��Ȼص���Ӧ�û�����
    fDownLoadDataCallBack: ¼�����ݻص�����(�ص���ʽ�ݲ�֧��ת��PS��)
    dwDataUser:     ¼�����ݻص���Ӧ�û�����
    scType:         ����ת������,0-DAV����(Ĭ��); 1-PS��
    pReserved:      �����ֶ�,������չ
�������	��	N/A
�� �� ֵ	��	LLONG ����¼����
����˵��	��	����ӿ�,SDKĬ�ϲ�֧��תPS��,�趨��SDK
******************************************************************************/
CLIENT_NET_API LLONG CALL_METHOD CLIENT_DownloadByRecordFileEx2(LLONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, 
                                                    fDownLoadPosCallBack cbDownLoadPos, LDWORD dwUserData, 
                                                    fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser, 
                                                    int scType = 0, void* pReserved = NULL);

/******************************************************************************
��������	:	ͨ��ʱ������¼��--��չ,�ɼ�������ת����
�������	:	
    lLoginID:       ��¼�ӿڷ��صľ��
    nChannelId:     ��Ƶͨ����,��0��ʼ
    nRecordFileType:¼������0 ����¼���ļ�
                            1 �ⲿ���� 
                            2 ��̬��ⱨ�� 
                            3 ���б��� 
                            4 ���Ų�ѯ  
                            5 ���������ѯ 
                            6 ¼��λ����ƫ�������� 
                            8 �����Ų�ѯͼƬ(Ŀǰ��HB-U��NVS�����ͺŵ��豸֧��) 
                            9 ��ѯͼƬ(Ŀǰ��HB-U��NVS�����ͺŵ��豸֧��)  
                            10 ���ֶβ�ѯ 
                            15 �����������ݽṹ(��������) 
                            16 ��ѯ����͸��������¼���ļ� 
    tmStart:        ��ʼʱ�� 
    tmEnd:          ����ʱ�� 
    sSavedFileName: ����¼���ļ���,֧��ȫ·��
    cbTimeDownLoadPos: ���ؽ��Ȼص�����(�ص����ؽ���,���ؽ��)
    dwUserData:     ���ؽ��Ȼص���Ӧ�û�����
    fDownLoadDataCallBack: ¼�����ݻص�����(�ص���ʽ�ݲ�֧��ת��PS��)
    dwDataUser:     ¼�����ݻص���Ӧ�û�����
    scType:         ����ת������,0-DAV����(Ĭ��); 1-PS��,3-MP4
    pReserved:      ��������,������չ
�������	��	N/A
�� �� ֵ	��	LLONG ����¼����
����˵��	��	����ӿ�,SDKĬ�ϲ�֧��תPS��,�趨��SDK
******************************************************************************/
CLIENT_NET_API LLONG CALL_METHOD CLIENT_DownloadByTimeEx2(LLONG lLoginID, int nChannelId, int nRecordFileType, 
                                                    LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, 
                                                    fTimeDownLoadPosCallBack cbTimeDownLoadPos, LDWORD dwUserData, 
                                                    fDataCallBack fDownLoadDataCallBack, LDWORD dwDataUser, 
                                                    int scType = 0, void* pReserved = NULL);

/******************************************************************************
��������	:	͸����չ�ӿ�,��͸�������߶�Ӧ͸����ʽ�ӿڣ�Ŀǰ֧��F6��͸��, ͬʱ����CLIENT_TransmitInfoForWeb�ӿ�
��������	:	
    lLoginID:       ��¼�ӿڷ��صľ��
    pInParam:       ͸����չ�ӿ��������
    pOutParam       ͸����չ�ӿ��������
    nWaittime       �ӿڳ�ʱʱ��

�� �� ֵ	��	BOOL  TRUE :�ɹ�; FALSE :ʧ��
******************************************************************************/
CLIENT_NET_API BOOL  CALL_METHOD CLIENT_TransmitInfoForWebEx(LLONG lLoginID, NET_IN_TRANSMIT_INFO* pInParam, 
                                                             NET_OUT_TRANSMIT_INFO* pOutParam, int nWaittime = 3000);


/******************************************************************************
��������	:	 �첽��͸�����Ľӿ�
��������	:	
    lLoginID:       ��¼�ӿڷ��صľ��
    pInParam:       �첽��͸���ӿ��������
    pOutParam       �첽��͸���ӿ��������
    nWaittime       �ӿڳ�ʱʱ��

�� �� ֵ	��	    LLONG �첽��͸�����
******************************************************************************/
CLIENT_NET_API LLONG CALL_METHOD CLIENT_AttachTransmitInfo(LLONG lLoginID, const NET_IN_ATTACH_TRANSMIT_INFO* pInParam, NET_OUT_ATTACH_TRANSMIT_INFO* pOutParam, int nWaitTime);

 

/******************************************************************************
��������	:	 �첽��͸��ȡ�����Ľӿ�
��������	:	
    lAttachHandle:  �첽��͸���������CLIENT_AttachTransmitInfo�ӿڵķ���ֵ
    pInParam:       �첽��͸��ȡ�����Ľӿ��������
    pOutParam       �첽��͸��ȡ�����Ľӿ��������
    nWaittime       �ӿڳ�ʱʱ��

�� �� ֵ	��		BOOL  TRUE :�ɹ�; FALSE :ʧ��
******************************************************************************/
CLIENT_NET_API BOOL  CALL_METHOD CLIENT_DetachTransmitInfo(LLONG lAttachHandle, const NET_IN_DETACH_TRANSMIT_INFO* pInParam, NET_OUT_DETACH_TRANSMIT_INFO* pOutParam, int nWaitTime);


/******************************************************************************
��������	:	 �豸������ƽӿ�
��������	:	
    lLoginID:                       ��¼�ӿڷ��صľ��
    EM_DEV_SPECIAL_CTRL_TYPE:       �����������
    pInParam:                       �豸������ƽӿ��������
    pOutParam                       �豸������ƽӿ��������
    nWaittime                       �ӿڳ�ʱʱ��

�� �� ֵ	��		BOOL  TRUE :�ɹ�; FALSE :ʧ��
******************************************************************************/
CLIENT_NET_API  BOOL CALL_METHOD CLIENT_DevSpecialCtrl(LLONG lLoginID, EM_DEV_SPECIAL_CTRL_TYPE emType, void* pInParam, void* pOutParam, int nWaitTime = 3000);


/******************************************************************************
��������	:	 ��ȡ�豸������Ϣ�ӿ�
��������	:	
    lLoginID:                       ��¼�ӿڷ��صľ��
    pstOutParam                     ��ȡ�豸������Ϣ�ӿڵ��������
    nWaittime                       �ӿڳ�ʱʱ��

�� �� ֵ	��		BOOL  TRUE :�ɹ�; FALSE :ʧ��
******************************************************************************/
CLIENT_NET_API  BOOL CALL_METHOD CLIENT_QueryEtherNetInfo(LLONG lLoginID, NET_DHDEV_ETHERNET_INFO* pstuOutParam, int nWaitTime = 3000);


/**************************************************************************************
*   Funcname: CLIENT_StartAsynRealPlay
*   Purpose:�����첽ʵʱ���ӽӿ�
*   InputParam:    LLONG                    :lLoginID    // ��½���
*   InputParam:    int                      :nChannelID  // ͨ����
*   InputParam:    HWND                     :hWnd        // ���ھ��
*   InputParam:    fAsynPlayHandleCallBack  :cbPlayHandle// �첽ʵʱ���Ӳ��ž���ص�
*   InputParam:    DH_RealPlayType          :rType       // ����������
*   InputParam:    fRealDataCallBackEx      :cbRealData  // ʵʱ�������ݻص�����
*   InputParam:    fRealPlayDisConnect      :cbDisconnect// ��Ƶ���ӶϿ��ص�����
*   InputParam:    LDWORD                   :dwUser      // �û�
*   InputParam:    DWORD                    :dwWaitTime  // �ȴ�ʱ��
*   Return:BOOL:FALSE,wrong;TRUE :right
*   Created:%2015%:%12%:%23%  
*   Revision Record:date:author:modify sth
**************************************************************************************/
CLIENT_NET_API BOOL CALL_METHOD CLIENT_StartAsynRealPlay(LLONG lLoginID, int nChannelID, HWND hWnd, fAsynPlayHandleCallBack cbPlayHandle, DH_RealPlayType rType, fRealDataCallBackEx cbRealData = NULL, fRealPlayDisConnect cbDisconnect = NULL, LDWORD dwUser = 0, DWORD dwWaitTime = 10000);

//////�Ϻ�BUS//////

// �������ݽ����ӿ�,�첽��ȡ����
CLIENT_NET_API LLONG CALL_METHOD CLIENT_ExChangeData(LLONG lLoginId, NET_IN_EXCHANGEDATA* pInParam, NET_OUT_EXCHANGEDATA* pOutParam, int nWaittime = 5000);

// ����CAN��������
CLIENT_NET_API LLONG CALL_METHOD CLIENT_AttachCAN(LLONG lLoginID, const NET_IN_ATTACH_CAN* pstInParam, NET_OUT_ATTACH_CAN* pstOutParam, int nWaitTime = 3000);

// ȡ������CAN�������ݣ�lAttachHandle��CLIENT_AttachCAN����ֵ
CLIENT_NET_API BOOL CALL_METHOD CLIENT_DetachCAN(LLONG lAttachHandle);

// ����CAN��������
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SendCAN(LLONG lLoginID, const NET_IN_SEND_CAN* pstInParam, NET_OUT_SEND_CAN* pstOutParam, int nWaitTime = 3000);

// ����͸����������
CLIENT_NET_API LLONG CALL_METHOD CLIENT_AttachDevComm(LLONG lLoginID, const NET_IN_ATTACH_DEVCOMM* pstInParam, NET_OUT_ATTACH_DEVCOMM* pstOutParam, int nWaitTime = 3000);

// ȡ������͸���������ݣ�lAttachHandle��CLIENT_AttachDevComm����ֵ
CLIENT_NET_API BOOL CALL_METHOD CLIENT_DetachDevComm(LLONG lAttachHandle);

// �Ϻ���ʿ�豸���ƽӿڣ���������PAD�ػ���������
CLIENT_NET_API BOOL CALL_METHOD CLIENT_ControlSpecialDevice(LLONG lLoginID, NET_SPECIAL_CTRL_TYPE emType, void* pInBuf, void* pOutBuf = NULL, int nWaitTime = NET_INTERFACE_DEFAULT_TIMEOUT);

//��ȡHCDZ�ɼ���Ϣ
CLIENT_NET_API BOOL  CALL_METHOD CLIENT_GetHCDZInfo(LLONG lLoginID, const NET_IN_HCDZ_LIST_INFO* pInParam, NET_OUT_HCDZ_LIST_INFO* pOutParam, int nWaitTime = 3000);

//��ȡHCDZ������
CLIENT_NET_API BOOL  CALL_METHOD CLIENT_GetHCDZCaps(LLONG lLoginID, const NET_IN_HCDZ_CAPS* pInParam, NET_OUT_HCDZ_CAPS* pOutParam, int nWaitTime = 3000);


// ������̨�����Կ�������ͼ���������öԵ�ǰ���е�¼����̨�豸����Ч����λms�����ʱ�������100ms��������Ч��
CLIENT_NET_API void CALL_METHOD CLIENT_PTZCmdSendIntervalTime(DWORD dwIntervalTime);

/**********************************************************************************
��������:��ȡHADT(ɽ����³��갲����)����״̬
��������:
    lLoginID:��¼�ӿڷ��صľ��
    pInBuf  :�������,���ʼ��dwSize
    pOutBuf :�������,���ʼ��dwSize
    nWaitTime :�ӿڳ�ʱʱ��
�� �� ֵ:	BOOL  TRUE :�ɹ�; FALSE :ʧ��
**********************************************************************************/
CLIENT_NET_API BOOL CALL_METHOD CLIENT_GetHADTStatus(LLONG lLoginID, const NET_IN_HADT_STATUS* pInBuf, NET_OUT_HADT_STATUS* pOutBuf,int nWaitTime = 3000);

/**********************************************************************************
��������:���Ʊ�����������ض��ƣ�
��������:
    lLoginID:��¼�ӿڷ��صľ��
    pInBuf  :�������,���ʼ��dwSize
    pOutBuf :�������,���ʼ��dwSize
    nWaitTime :�ӿڳ�ʱʱ��
�� �� ֵ:	BOOL  TRUE :�ɹ�; FALSE :ʧ��
**********************************************************************************/
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetAlarmOut(LLONG lLoginID, const NET_IN_SET_ALARMOUT* pInBuf, NET_OUT_SET_ALARMOUT* pOutBuf,int nWaitTime);

//����EVS��ʱ¼��
CLIENT_NET_API BOOL CALL_METHOD CLIENT_StartLinkRecord(LLONG lLoginID, const NET_IN_LINK_RECORD_CTRL *pstIn, NET_OUT_LINK_RECORD_CTRL *pstOut, int nWaitTime);

// �����������ƽӿڣ�����Ukeyֵ
/**********************************************************************************
��������:�豸�˴ε�½��Ukeyֵ
��������:
    lLoginID:��¼�ӿڷ��صľ��
    pInBuf  :�������,���ʼ��dwSize
    pOutBuf :�������,���ʼ��dwSize
    nWaitTime :�ӿڳ�ʱʱ��
�� �� ֵ:	BOOL  TRUE :�ɹ�; FALSE :ʧ��
**********************************************************************************/
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetDeviceUkey(LLONG lLoginID, const NET_IN_SET_UEKY *pInBuf, NET_OUT_SET_UEKY *pOutBuf, int nWaitTime);

typedef struct tagNET_IN_NETACCESS
{
	DWORD		dwSize;									// �ṹ���С
	char		szMac[DH_MACADDR_LEN];					// �豸mac��ַ
	char		szSecurity[MAX_SECURITY_CODE_LEN];		// ��ȫ��
	BYTE		byInitStaus;							// �豸��ʼ��״̬�������豸�ӿ�(CLIENT_SearchDevices��CLIENT_StartSearchDevices�Ļص�������CLIENT_SearchDevicesByIPs)�����ֶ�byInitStatus��ֵ
	BYTE		byReserved[3];							// �����ֶ�
}NET_IN_NETACCESS;
typedef struct tagNET_OUT_NETACCESS
{
	DWORD		dwSize;					// �ṹ���С
}NET_OUT_NETACCESS;
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetNetAccess(const NET_IN_NETACCESS* pNetAccessIn, NET_OUT_NETACCESS* pNetAccessOut, DWORD dwWaitTime, char* szLocalIp);

// ��ӦCLIENT_StartSearchCustomDevices�ӿ�
// ����OEM�豸����ö��
typedef enum tagEM_SEARCH_OEM_DEVICE_TYPE
{
	EM_TYPE_JIANGSU_CHUANGTONG = 0,    // ���մ�ͨOEM�豸����
	EM_TYPE_MAX,					   // ���ö��ֵ
}EM_SEARCH_OEM_DEVICE_TYPE;

// OEM�豸��Ϣ
typedef struct tagCUSTOM_DEVICE_NETINFO
{
	char                szMac[DH_MACADDR_LEN];                  // MAC��ַ,��00:40:9D:31:A9:0A
	char                szIP[DH_MAX_IPADDR_EX_LEN];				// IP��ַ,��10.0.0.231
	char                szDevName[DH_MACHINE_NAME_NUM];         // �豸����,�̶�ΪWireless Transmission Device
	BYTE				byReserved[1024];						// �����ֽ�
}CUSTOM_DEVICE_NETINFO;

// �첽����OEM�豸�ص���pCustomDevNetInf�ڴ���SDK�ڲ������ͷţ�
typedef void (CALLBACK *fSearchCustomDevicesCB)(CUSTOM_DEVICE_NETINFO *pCustomDevNetInfo, void* pUserData);

// CLIENT_StartSearchCustomDevices�ӿڵ��������
typedef struct tagNET_IN_SEARCH_PARAM 
{
	DWORD							dwSize;                  // �ṹ���С
	fSearchCustomDevicesCB			cbFunc;			         // ����OEM�豸�ص�����
	void*							pUserData;               // �û�������Զ�������
	char*							szLocalIp;				 // ����IP
	EM_SEARCH_OEM_DEVICE_TYPE       emSearchOemDeviceType;   //	����OEM�豸����
}NET_IN_SEARCH_PARAM;

// CLIENT_StartSearchCustomDevices���������
typedef struct tagNET_OUT_SEARCH_PARAM
{
	DWORD		dwSize;
}NET_OUT_SEARCH_PARAM;

// �첽�鲥����OEM�豸, (pInParam, pOutParam�ڴ����û������ͷ�),��֧�ֶ��̵߳���,�����Ʒ������
CLIENT_NET_API LLONG CALL_METHOD CLIENT_StartSearchCustomDevices(const NET_IN_SEARCH_PARAM *pInParam, NET_OUT_SEARCH_PARAM *pOutParam); 
// ֹͣ�鲥����OEM�豸
CLIENT_NET_API BOOL CALL_METHOD CLIENT_StopSearchCustomDevices(LLONG lSearchHandle);

// �豸��¼�������
typedef struct tagNET_IN_LOGIN_POLICY_PARAM
{
	DWORD               dwSize;
	int		            nDevicePort;							// �豸�˿ں�
	char		        *szDeviceIp;			                // �豸ip��ַ    
	char		        *szUserName;		                    // �û���
	char 		        *szPassword;		                    // �û�����

	EM_LOGIN_SPAC_CAP_TYPE 		emSpecCap;				        // ��½����, Ŀǰ��֧�� TCP / Mobile / P2P ��¼
	void	            *pCapParam; 							// ��½��������, ����������emSpeCap���

	int                 nLoginPolicyFlag;                       // ��¼���Ա�־λ
	// bit0 == 1 ���ٵ�¼: �豸��Ϣ ���к�/��������/���������Ч 

	int                 nPlayPolicyFlag;                        // ʵʱԤ�����Ա�־λ
	// bit0 == 1 ��֧�ֻ��л�

	int                 nPlayBackPolicyFlag;					// ¼��طź�¼���ѯ���Ա�־λ
	// bit0 == 1 ����ѯ���л�����

}NET_IN_LOGIN_POLICY_PARAM;

// �豸��¼���Գ���
typedef struct tagNET_OUT_LOGIN_POLICY_PARAM
{
	DWORD               dwSize;
	NET_DEVICEINFO_Ex   stuDeviceInfo;                          // �豸��Ϣ
}NET_OUT_LOGIN_POLICY_PARAM;


// ��¼��չ�ӿ�, ֧�ֲ���
CLIENT_NET_API LLONG CALL_METHOD CLIENT_LoginWithPolicy(const NET_IN_LOGIN_POLICY_PARAM* pstInParam, NET_OUT_LOGIN_POLICY_PARAM* pstOutParam, int nWaitTime);

// �����Ż�ģʽ
typedef enum __EM_LOCAL_MODE
{
	EM_LOCAL_PLAY_FLAG_MODE = 101,      // ʵʱԤ�����Ա�־λ  bit0 == 1 ��֧�ֻ��л�  bit1 == 1 ��֧��ͨ����ϢУ�� 
	EM_LOCAL_PLAYBACK_FLAG_MODE = 102,  // ¼��طź�¼���ѯ���Ա�־λ  bit0 == 1 ��֧�ֻ��л�
} EM_LOCAL_MODE;

// ���ñ���һЩ������Ż�ģʽ
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetLocalMode(LLONG lLoginID, EM_LOCAL_MODE emType, void* pValue);


// CLIENT_TriggerAutoInspection �ӿ����
typedef struct tagNET_IN_TRIGGER_AUTO_INSPECTION
{
	DWORD dwSize;
}NET_IN_TRIGGER_AUTO_INSPECTION;

// CLIENT_TriggerAutoInspection �ӿڳ���
typedef struct tagNET_OUT_TRIGGER_AUTO_INSPECTON
{
	DWORD dwSize;
}NET_OUT_TRIGGER_AUTO_INSPECTON;

// �����豸�Լ죨¥���Ʒ��ר������
CLIENT_NET_API BOOL CALL_METHOD CLIENT_TriggerAutoInspection(LLONG lLoginID, const NET_IN_TRIGGER_AUTO_INSPECTION* pstInParam, NET_OUT_TRIGGER_AUTO_INSPECTON* pstOutParam, int nWaitTime);

// CLIENT_GetLicenseAssistInfo �ӿ����
typedef struct tagNET_IN_GET_LICENSE_INFO
{
	DWORD dwSize;								// ��ֵΪ�ṹ���С
}NET_IN_GET_LICENSE_INFO;

// ��Ҫ��License���ƵĿ���Ϣ
typedef struct tagNET_RESTRICTED_LIB_INFO
{
	char szId[40];								// �����ƿ�Id
	char szVersion[32];							// �����ƿ�İ汾
	char szKey1[128];							// ����Ҫ���ض���Ϣ1���������������ƿ�ȷ��
	char szKey2[128];							// ����Ҫ���ض���Ϣ2���������������ƿ�ȷ��
	char szKey3[128];							// ����Ҫ���ض���Ϣ3���������������ƿ�ȷ��
	char szKey4[128];							// ����Ҫ���ض���Ϣ4���������������ƿ�ȷ��
	char szReserved[1024];						// �����ֶ�
}NET_RESTRICTED_LIB_INFO;

// CLIENT_GetLicenseAssistInfo �ӿڳ���
typedef struct tagNET_OUT_GET_LICENSE_INFO
{
	DWORD dwSize;								// ��ֵΪ�ṹ���С
	char  szSeriesNum[32];						// �豸���к�
	char  szMac[8][32];							// �豸Mac ��ַ
	int   nMacRet;								// ���ص�Mac��ַ����
	char  szBindInfo[256];						// ����Ϣ
	char  szAppVersion[32];						// Ӧ�ó���汾
	char  szAppVerificationCode[512];			// Ӧ�ó���У����Ϣ	
	char  szLicenseLibVsersion[32];				// License �����汾��Ϣ
	NET_RESTRICTED_LIB_INFO stuLibInfo[8];		// ��Ҫ��License���ƵĿ���Ϣ
	int	  nLibInfoRet;							// ���ص�stuLibInfo�ṹ������
}NET_OUT_GET_LICENSE_INFO;

// ��ȡ����License�ĸ�����Ϣ
CLIENT_NET_API BOOL CALL_METHOD CLIENT_GetLicenseAssistInfo(LLONG lLoginID, const NET_IN_GET_LICENSE_INFO* pstInParam, NET_OUT_GET_LICENSE_INFO* pstOutParam, int nWaitTime);

// CLIENT_SetLicense �ӿ����
typedef struct tagNET_IN_SET_LICENSE
{
	DWORD dwSize;								// ��ֵΪ�ṹ���С
	char  szLicenseInfo[8192];					// License ����
	char  szSignature[512];						// License ���ݵ�����ǩ��
}NET_IN_SET_LICENSE;

// CLIENT_SetLicense �ӿڳ���
typedef struct tagNET_OUT_SET_LICENSE
{
	DWORD dwSize;								// ��ֵΪ�ṹ���С
}NET_OUT_SET_LICENSE;

// ����License
CLIENT_NET_API BOOL CALL_METHOD CLIENT_SetLicense(LLONG lLoginID, const NET_IN_SET_LICENSE* pstInParam, NET_OUT_SET_LICENSE* pstOutParam, int nWaitTime);

// ��ȡ�豸״̬���
typedef struct tagNET_IN_UNIFIEDINFOCOLLECT_GET_DEVSTATUS
{
    DWORD               dwSize;                                 // �ṹ���С
}NET_IN_UNIFIEDINFOCOLLECT_GET_DEVSTATUS;

// ��������
typedef enum tagNET_EM_POWER_TYPE
{
    NET_EM_POWER_TYPE_UNKNOWN = -1,                     // δ֪              
    NET_EM_POWER_TYPE_POWERADAPTER,                     // ��Դ������
    NET_EM_POWER_TYPE_BATTERY,                          // ���
    NET_EM_POWER_TYPE_BATTERY_AND_POWERADAPTER,         // ���+��Դ������
}NET_EM_POWER_TYPE;

// ��Դ��������Ϣ
typedef struct tagNET_DEVSTATUS_POWER_INFO
{
	UINT                nBatteryPercent;                        // ��ص����ٷֱ�,0~100
    NET_EM_POWER_TYPE   emPowerType;                            // ��������
}NET_DEVSTATUS_POWER_INFO;

// ����������״̬
typedef enum tagNET_EM_ETH_STATE
{
    NET_EM_ETH_UNKNOWN,                                         // δ֪
    NET_EM_ETH_CONNECT,                                         // ����
    NET_EM_ETH_DISCONNECT,                                      // δ����
}NET_EM_ETH_STATE;

// ���������Ϣ
typedef struct tagNET_DEVSTATUS_NET_INFO
{
    UINT                nWifiIntensity;                         // wifi�ź�ǿ�ȵȼ���0~5��0��ʾû���ź�
    UINT                nWifiSignal;                            // wifi�ź�ǿ�ȣ���λdbm, 0~100,0��ʾû���ź�
    UINT                nCellulSignal;                          // 2g/3g/4g�ź�ǿ��,��λdbm. 0~100, 0��ʾû���ź�
    UINT                nCellulIntensity;                       // 2g/3g/4g�ź�ǿ�ȵȼ�,0~5, 0��ʾû���ź�
    NET_EM_ETH_STATE    emEthState;                             // ����������״̬
    UINT                n3Gflux;                                // ��������ʵ��ʹ����������λ��MB
    UINT                n3GfluxByTime;                          // ����ʵ��ʹ��ʱ������λ������     
}NET_DEVSTATUS_NET_INFO;

// ��������״̬
typedef enum tagNET_EM_TAMPER_STATE
{
    NET_EM_TAMPER_UNKNOWN = -1,                             // δ֪ 
    NET_EM_TAMPER_NOALARM,                                  // δ����
    NET_EM_TAMPER_ALARMING,                                 // ������
}NET_EM_TAMPER_STATE;

// ��ȡ�豸״̬����
typedef struct tagNET_OUT_UNIFIEDINFOCOLLECT_GET_DEVSTATUS
{
    DWORD                           dwSize;                         // �ṹ���С
    NET_DEVSTATUS_POWER_INFO        stuPowerInfo;                   // ��Դ��������Ϣ
    NET_DEVSTATUS_NET_INFO          stuNetInfo;                     // ���������Ϣ
    char                            szVersion[DH_COMMON_STRING_32]; // ��������汾
    NET_EM_TAMPER_STATE             emTamperState;                  // ��������״̬
}NET_OUT_UNIFIEDINFOCOLLECT_GET_DEVSTATUS;

// ��ȡ�豸״̬, DMSSר�ýӿ�, pInParam��pOutParam�ڴ����û������ͷ�
CLIENT_NET_API BOOL CALL_METHOD CLIENT_GetUnifiedStatus(LLONG lLoginID, NET_IN_UNIFIEDINFOCOLLECT_GET_DEVSTATUS* pInParam, NET_OUT_UNIFIEDINFOCOLLECT_GET_DEVSTATUS* pOutParam, int nWaitTime);

// CLIENT_QueryUserRights �ӿ��������
typedef struct tagNET_IN_QUERYUSER_RIGHT
{
	DWORD				dwSize; 					// �˽ṹ���С			
} NET_IN_QUERYUSER_RIGHT;

// CLIENT_QueryUserRights �ӿ��������
typedef struct tagNET_OUT_QUERYUSER_RIGHT
{
	DWORD				dwSize; 					// �˽ṹ���С		
	DWORD				dwRightNum; 				// Ȩ����Ϣ
	OPR_RIGHT_NEW		rightList[DH_NEW_MAX_RIGHT_NUM];					  
	USER_INFO_NEW		userInfo;					// �û���Ϣ
	DWORD				dwFunctionMask; 			// ���룻0x00000001 - ֧���û����ã�0x00000002 - �����޸���ҪУ��
} NET_OUT_QUERYUSER_RIGHT;

// APP�û������Ż��ӿ�
CLIENT_NET_API BOOL CALL_METHOD CLIENT_QueryUserRights(LLONG lLoginID, const NET_IN_QUERYUSER_RIGHT* pstInParam, NET_OUT_QUERYUSER_RIGHT* pstOutParam ,int waittime);

#ifdef __cplusplus
}
#endif



#endif // DHNETSDKEX_H



