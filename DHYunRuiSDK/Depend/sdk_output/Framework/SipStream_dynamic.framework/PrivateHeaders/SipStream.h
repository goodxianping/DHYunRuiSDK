#pragma once
#include "MediaStreamFactory/BaseMediaStream.h"
#include "Infra/Timer.h"
#include "Infra/Mutex.h"

#include "PlatformSDK/DPSDKTalk.h"
#include "PlatformSDK/DPSDKCall.h"

namespace Dahua {
    namespace LCCommon {
class CSipStream: public CBaseMediaStream
{
public:
    void*                m_dpHandle;
private:
	DPSdk::IDPSDKCall*	m_pDPSDKCallInterface;
	void*				m_sendDataFunction;
    DPSdk::AudioUserParam_t*	m_pSdkAudioUser;
    bool            		m_isPlayReady;
    Dahua::Infra::CTimer *timer;
    Dahua::Infra::CMutex   m_listenMutex;
    IMediaStreamListener*   m_listener;

private:
	static int SipMediaDataCallbackForTalk( int session, DPSdk::dpsdk_media_func_e mediaType, const char* nodeId, int paramVal, char* pData, int dataLen, void* pUserParam);
    void timerOnState(unsigned long arg);

public:
	CSipStream();
	~CSipStream(void);
	
	void onState(int error);
    long getRecvAudioCallBack();
public:
    virtual bool isRealStream(){return false;}
    virtual bool isPlayBackStream() {return false;}
    virtual bool isTalkStream() {return true;}
    
    /* »°÷µ£∫STREAM_TYPE_REAL_STREAM / STREAM_TYPE_RECORD_STREAM / STREAM_TYPE_RECORD_FILE */
    virtual int getStreamType(){return -1;}
    
    /* getStreamƒ⁄≤øµ˜∏ˆ–≠“Èø‚Ω”ø⁄¿≠¡˜ ±£¨ «Õ¨≤ΩΩ”ø⁄ªπ «“Ï≤ΩΩ”ø⁄£¨±»»Ártsp «“Ï≤Ω£¨netsdk «Õ¨≤Ω */
    virtual bool isAsync() {return true;}
    
    virtual const char* getIdentity() {return "";}
    
    virtual void setListener(IMediaStreamListener* listener);
    virtual IMediaStreamListener* getListener();
    virtual void setParams(const char* className, const char* jsonParams);
    
    virtual int getStream();
    virtual int closeStream();
    virtual int pauseStream(){return  -1;}
    virtual int resumeStream(){return -1;}
    virtual int seekStream(int seconds) {return  -1;}
    
    virtual int getDuration() {return -1;}
    virtual int setStreamSpeed(float speed, float offsetSeconds){return -1;}
    virtual float getStreamSpeed() {return 1;}
    virtual int setStreamDirection(bool bDir,int offSecs) {return -1;}
    
    virtual int sendAudioData(unsigned char* audioData, int offset, int len);
};
}
}

