#pragma once

#include "common.h"
#include <list>
#include <sipLocalConfig.h>
#include <sip.h>
#include <ThreadPool.h>
#include <sys/time.h>
#include <sipDef.h>

//用于控制所有的全局变量
class GlobalCtl;
#define  GBOJ(obj)  GlobalCtl::instance()->obj

static pj_status_t pjcall_thread_register(pj_thread_desc& desc)
{
    pj_thread_t* tread = 0;
    if(!pj_thread_is_registered())
    {
        return pj_thread_register(NULL,desc,&tread);
    }
    return PJ_SUCCESS;
}


class Session
{
    public:
        Session(const DeviceInfo& devInfo)
        {
            devid = devInfo.devid;
            platformId = devInfo.playformId;
            streamName = devInfo.streamName;
            setupType = devInfo.setupType;
            protocal = devInfo.protocal;
            startTime = devInfo.startTime;
            endTime = devInfo.endTime;
            gettimeofday(&m_curTime,NULL);
			rtp_loaclport = 0;
        }
        
        virtual ~Session()
        {

        }

    public:
        string devid;
		string platformId;
		string streamName;
		string setupType;
		int protocal;
		int startTime;
		int endTime;
        timeval m_curTime;
		int rtp_loaclport;
};

class GlobalCtl
{
    public:
        static GlobalCtl* instance();
        bool init(std::shared_ptr<SipLocalConfig> );

        std::shared_ptr<SipLocalConfig> gConfig = nullptr;
        std::shared_ptr<ThreadPool> gThPool = nullptr;
        std::shared_ptr<SipCore> gSipServer = nullptr;


        static std::string catalogPayLoadIn;
        typedef struct _SubDomainInfo
        {
            _SubDomainInfo()
            {
                sipId = "";
                addrIp = "";
                sipPort = 0;
                protocal = 0;
                registered = false;
                expires = 0;
                lastRegTime = 0;
                auth = false;
            }

            bool operator==(string id)
            {
                return (this->sipId == id);
            }
            string sipId;
            string addrIp;
            int sipPort;
            int protocal;
            bool registered;
            int expires;
            time_t lastRegTime;
            bool auth;
        }SubDomainInfo;
        typedef list<SubDomainInfo> SUBDOMAININFOLIST;

        SUBDOMAININFOLIST& getSubDomainInfoList()
        {
            return subDomainInfoList;
        }

        static void get_global_mutex()
        {
            pthread_mutex_lock(&globalLock);
        }

        static void free_global_mutex()
        {
            pthread_mutex_unlock(&globalLock);
        }
        

        typedef list<Session*> ListSession;


        static ListSession glistSession;

        static pthread_mutex_t gStreamLock;
        static pthread_mutex_t globalLock;

        static bool gStopPool;
        static bool gRcvIpc;
    public:
        static bool checkIsExist(string id);
        static bool checkIsVaild(string id);
        static void setExpires(string id,int expires);
        static void setRegister(string id,bool registered);
        static void setLastRegTime(string id,time_t t);
        static bool getAuth(string id);
        static DevTypeCode getSipDevInfo(string id);

        static string randomNum(int length);
    private:
        GlobalCtl(void)
        {

        }
        ~GlobalCtl(void);
        GlobalCtl(const GlobalCtl& global);
        const GlobalCtl& operator=(const GlobalCtl& global);

        static GlobalCtl* m_pInstance;
        static SUBDOMAININFOLIST subDomainInfoList;
        
};
