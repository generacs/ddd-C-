#pragma once

#include <SipTaskBase.h>

class SipDirectory : public SipTaskBase
{
    public:
        SipDirectory(tinyxml2::XMLElement* root);
        ~SipDirectory();
        virtual pj_status_t run(pjsip_rx_data *rdata);
        void SaveDir(int& status_code);
    private:
        tinyxml2::XMLElement* m_pRootElement;
};