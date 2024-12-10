#include "sipGbPlay.h"
#include "sipGb28281Session.h"

SipGbPlay::SipGbPlay()
{

}

SipGbPlay::~SipGbPlay()
{

}

void SipGbPlay::OnStateChanged(pjsip_inv_session *inv, pjsip_event *e)
{
	LOG(INFO)<<"OnStateChanged";
}
void SipGbPlay::OnNewSession(pjsip_inv_session *inv, pjsip_event *e)
{
	LOG(INFO)<<"OnNewSession";
}
void SipGbPlay::OnMediaUpdate(pjsip_inv_session *inv_ses, pj_status_t status)
{
    LOG(INFO) << "OnMediaUpdate";
    if(NULL == inv_ses)
    {
        return;
    }
    
    pjsip_tx_data* tdata;
    const pjmedia_sdp_session* remote_sdp = NULL;
    pjmedia_sdp_neg_get_active_remote(inv_ses->neg,&remote_sdp);
    if(NULL == remote_sdp)
    {
        pjsip_inv_end_session(inv_ses,PJSIP_SC_UNSUPPORTED_MEDIA_TYPE,NULL,&tdata);
        pjsip_inv_send_msg(inv_ses,tdata);
        return;
    }

    if(remote_sdp->media_count <= 0 || NULL == remote_sdp->media[remote_sdp->media_count-1])
    {
        pjsip_inv_end_session(inv_ses,PJSIP_SC_FORBIDDEN,NULL,&tdata);
        pjsip_inv_send_msg(inv_ses,tdata);
        return;
    }
    pjmedia_sdp_media* m = remote_sdp->media[remote_sdp->media_count-1];
    int sdp_port = m->desc.port;

    pjmedia_sdp_conn* c = remote_sdp->conn;
    string ip(c->addr.ptr,c->addr.slen);

    LOG(INFO)<<"remote rtp ip:"<<ip<<" remote rtp port:"<<sdp_port;

    Gb28181Session* rtpsession = dynamic_cast<Gb28181Session*>((Session*)inv_ses->mod_data[0]);
    rtpsession->CreateRtpSession(ip,sdp_port);

    return;

}

void SipGbPlay::OnSendAck(pjsip_inv_session *inv, pjsip_rx_data *rdata){
    LOG(INFO) << "OnSendAck" ;
    return;
}