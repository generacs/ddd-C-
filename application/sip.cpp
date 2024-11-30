#include "sip.h"
#include <iostream>
#include <string>
#include <sipGbPlay.h>
#include <thread>
#include <globalCtl.h>
using namespace std;


static int pollingEvent(void* arg){
    LOG(INFO)<<"polling event thread start success";
    pjsip_endpoint* ept = (pjsip_endpoint*)arg;

    while(true){
        pj_time_val timeout = {0,500};
        pj_status_t status = pjsip_endpt_handle_events(ept,&timeout);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"polling events failed,code:"<<status;
            return -1;
        }
    }
    return 0;
}

//应用层处理入口，处理接受响应
pj_bool_t onRxRequest(pjsip_rx_data *rdata){
    if(NULL == rdata || NULL == rdata->msg_info.msg)
    {
        return PJ_FALSE;
    }
    threadParam* param = new threadParam();
    pthread_t pid;
    int ret = EC::ECThread::createThread(SipCore::dealTaskThread,param,pid);
    if(ret != 0)
    {
        LOG(ERROR)<<"create task thread error";
        if(param)
        {
            delete param;
            param = NULL;
        }
        return PJ_FALSE;
    }
    return PJ_SUCCESS;
}

static pjsip_module recv_mod=
{
    NULL,NULL,
    {"mod-recv",8},
    -1,
    PJSIP_MOD_PRIORITY_APPLICATION,
    NULL,
    NULL,
    NULL,
    NULL,
    onRxRequest,
    NULL,
    NULL,
    NULL,
    NULL,
};

SipCore::SipCore()
:m_endpt(NULL)
{

}
SipCore::~SipCore()
{
    pjmedia_endpt_destroy(m_mediaEndpt);
    pjsip_endpt_destroy(m_endpt);
    pj_caching_pool_destroy(&m_cachingPool);
    pj_shutdown();
    // GlobalCtl::gStopPool = true;
}

void SipCore::stopSip()
{
	pjmedia_endpt_destroy(m_mediaEndpt);
    pjsip_endpt_destroy(m_endpt);
    pj_caching_pool_destroy(&m_cachingPool);
    pj_shutdown();
    // GlobalCtl::gStopPool = true;
}

void* SipCore::dealTaskThread(void* arg)
{
    threadParam* param = (threadParam*)arg;
    if(!param || param->base == NULL)
    {
        return NULL;
    }
    pj_thread_desc desc;
    pjcall_thread_register(desc);
    param->base->run(param->data);
    delete param;
    param = NULL;
    return nullptr;
}

bool SipCore::InitSip(int sipPort)
{
    pj_status_t status;
    //0-关闭  6-详细
    pj_log_set_level(0);

    do
    {

        status = pj_init();
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"init pjlib faild,code:"<<status;
            break;
        }
        status = pjlib_util_init();
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"init pjlib util faild,code:"<<status;
            break;
        }

        pj_caching_pool_init(&m_cachingPool,NULL,10086);

        status = pjsip_endpt_create(&m_cachingPool.factory,NULL,&m_endpt);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"create endpt faild,code:"<<status;
            break;
        }

        pj_ioqueue_t* ioqueue = pjsip_endpt_get_ioqueue(m_endpt);
        status = pjmedia_endpt_create(&m_cachingPool.factory,ioqueue,0,&m_mediaEndpt);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"create media endpoint faild,code:"<<status;
            break;
        }

        status = pjsip_tsx_layer_init_module(m_endpt);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"init tsx layer faild,code:"<<status;
            break;
        }

        status = pjsip_ua_init_module(m_endpt,NULL);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"init UA layer faild,code:"<<status;
            break;
        }

        //初始化传输层模块
        status = init_transport_layer(sipPort);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"init transport layer faild,code:"<<status;
            break;
        }


        status = pjsip_endpt_register_module(m_endpt,&recv_mod);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"register recv module faild,code:"<<status;
            break;
        }


        status = pjsip_100rel_init_module(m_endpt);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"100rel module init faild,code:"<<status;
            break;
        }

        pjsip_inv_callback inv_cb;
        pj_bzero(&inv_cb,sizeof(inv_cb));
        inv_cb.on_state_changed = &SipGbPlay::OnStateChanged;
        inv_cb.on_new_session = &SipGbPlay::OnNewSession;
        inv_cb.on_media_update = &SipGbPlay::OnMediaUpdate;
        inv_cb.on_send_ack = &SipGbPlay::OnSendAck;
        status = pjsip_inv_usage_init(m_endpt,&inv_cb);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"register invite module faild,code:"<<status;
            break;
        }

        m_pool = pjsip_endpt_create_pool(m_endpt,NULL, PJ::MemorySize ,PJ::MemorySize);
        if(NULL == m_pool)
        {
            LOG(ERROR)<<"create pool faild";
            break;
        }

        pj_thread_t* eventThread = NULL;
        status = pj_thread_create(m_pool,NULL,&pollingEvent,m_endpt,0,0,&eventThread);
        
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"create pjsip thread faild,code:"<<status;
            break;
        }
    } while (0);

    bool bret = true;
    if(PJ_SUCCESS != status)
    {
        bret = false;
    }
    return bret;
    
}

pj_status_t SipCore::init_transport_layer(int sipPort)
{
    pj_sockaddr_in addr;
    pj_bzero(&addr,sizeof(addr));
    addr.sin_family = pj_AF_INET();
    addr.sin_addr.s_addr = 0;
    addr.sin_port = pj_htons((pj_uint16_t)sipPort);

    pj_status_t status;
    do
    {
        status = pjsip_udp_transport_start(m_endpt,&addr,NULL,1,NULL);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"start udp server faild,code:"<<status;
            break;
        }

        status = pjsip_tcp_transport_start(m_endpt,&addr,1,NULL);
        if(PJ_SUCCESS != status)
        {
            LOG(ERROR)<<"start tcp server faild,code:"<<status;
            break;
        }

        LOG(ERROR)<<"sip tcp:"<<sipPort<<" udp:"<<sipPort<<" running";
    } while (0);
    
    return status;
}