#include "sipGbPlay.h"

SipGbPlay::SipGbPlay()
{

}

SipGbPlay::~SipGbPlay()
{

}

void SipGbPlay::OnStateChanged(pjsip_inv_session *inv, pjsip_event *e)
{
	std::cout<<"OnStateChanged";
}
void SipGbPlay::OnNewSession(pjsip_inv_session *inv, pjsip_event *e)
{
	std::cout<<"OnNewSession";
}
void SipGbPlay::OnMediaUpdate(pjsip_inv_session *inv_ses, pj_status_t status)
{

    return;

}

void SipGbPlay::OnSendAck(pjsip_inv_session *inv, pjsip_rx_data *rdata){
    return;
}