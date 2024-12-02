#pragma once
#include "common.h"
#include "pjsipCommon.h"

class SipTaskBase
{
    public:
        SipTaskBase(){}
        virtual ~SipTaskBase()
        {
            LOG(INFO)<<"~SipTaskBase";
        }

        virtual pj_status_t run(pjsip_rx_data *rdata) = 0;

        static tinyxml2::XMLElement* parseXmlData(pjsip_msg* msg,string& rootType,const string xmlkey,string& xmlvalue);
    protected:
        string parseFromId(pjsip_msg* msg);
};