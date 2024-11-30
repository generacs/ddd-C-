// 首先创建一个sip服务，用于通信， 使用pjsip库
#pragma once
#include <pjsipCommon.h>
#include <SipTaskBase.h>

typedef struct _threadParam
{
    _threadParam()
    {
        base = NULL;
        data = NULL;
    }
    ~_threadParam()
    {
        if(base)
        {
            delete base;
            base = NULL;
        }
        if(data)
        {
            pjsip_rx_data_free_cloned(data);
            base = NULL;
        }
    }
    SipTaskBase* base;
    pjsip_rx_data* data;
}threadParam;



class SipCore
{
    public:
        SipCore();
        ~SipCore();

        bool InitSip(int sipPort);

        pj_status_t init_transport_layer(int sipPort);

        pjsip_endpoint* GetEndPoint(){return m_endpt;}
        pj_pool_t* GetPool(){return m_pool;}
		void stopSip();
    public:
        static void* dealTaskThread(void* arg);

    private:
        pjsip_endpoint* m_endpt;
        pjmedia_endpt* m_mediaEndpt;
        pj_caching_pool m_cachingPool;
        pj_pool_t* m_pool;
};