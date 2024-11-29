#include <pjsipCommon.h>

class SipGbPlay
{
    public:
        SipGbPlay();
        ~SipGbPlay();

        static void OnStateChanged(pjsip_inv_session *inv, pjsip_event *e);
        static void OnNewSession(pjsip_inv_session *inv, pjsip_event *e);
        static void OnMediaUpdate(pjsip_inv_session *inv_ses, pj_status_t status);
		static void OnSendAck(pjsip_inv_session *inv, pjsip_rx_data *rdata);
};

