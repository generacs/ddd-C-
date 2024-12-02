#include "sipHeartBeat.h"

SipHeartBeat::SipHeartBeat()
{

}

SipHeartBeat::~SipHeartBeat()
{

}

pj_status_t SipHeartBeat::run(pjsip_rx_data *rdata)
{
    return HeartBeatMessage(rdata);
}

pj_status_t SipHeartBeat::HeartBeatMessage(pjsip_rx_data *rdata)
{
    LOG(INFO)<<"HeartBeatMessage";
    pjsip_msg* msg = rdata->msg_info.msg;
    string fromId = parseFromId(msg);
    time_t regTime = 0;
    struct sysinfo info;
    memset(&info,0,sizeof(info));
    int ret = sysinfo(&info);
    if(ret == 0)
    {
        regTime = info.uptime;
    }
    else
    {
        regTime = time(NULL);
    }
    int status_code = 200;
    AutoMutexLock lck(&GlobalCtl::globalLock);
    GlobalCtl::SUBDOMAININFOLIST::iterator it;
    it = std::find(GlobalCtl::instance()->getSubDomainInfoList().begin(),GlobalCtl::instance()->getSubDomainInfoList().end(),fromId);
    if(it != GlobalCtl::instance()->getSubDomainInfoList().end() && it->registered)
    {
        it->lastRegTime = regTime;
    }
    else
    {
        status_code = 403;
    }

    pj_status_t status = pjsip_endpt_respond(GBOJ(gSipServer)->GetEndPoint(),NULL,rdata,status_code,NULL,NULL,NULL,NULL);
    if(PJ_SUCCESS != status)
    {
        LOG(ERROR)<<"pjsip_endpt_respond error";
    }
    
    return status;
}