#pragma once

#include "SipTaskBase.h"
#include <globalCtl.h>
#include <common.h>


class SipHeartBeat : public SipTaskBase{
    public:
        SipHeartBeat();
        ~SipHeartBeat();

        virtual pj_status_t run(pjsip_rx_data *rdata);
        pj_status_t HeartBeatMessage(pjsip_rx_data *rdata);
};