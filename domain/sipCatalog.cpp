#include "sipCatalog.h"
#include <globalCtl.h>
#include <sipMessage.h>
#include <XmlParser.h>
#include <thread>

SipCatalog::SipCatalog()
{
    DirectoryGetPro(nullptr);
}

SipCatalog::~SipCatalog()
{

}

void SipCatalog::DirectoryGetPro(void* param)
{
    SipMessage msg;
    AutoMutexLock lock(&(GlobalCtl::globalLock));

    GlobalCtl::SUBDOMAININFOLIST::iterator iter = GlobalCtl::instance()->getSubDomainInfoList().begin();
    for(;iter != GlobalCtl::instance()->getSubDomainInfoList().end(); iter++)
    {
        XmlParser parse;
        if(iter->registered)
        {
            msg.setFrom((char*)GBOJ(gConfig)->sipId().c_str(),(char*)GBOJ(gConfig)->sipIp().c_str());
            msg.setTo((char*)iter->sipId.c_str(),(char*)iter->addrIp.c_str());
            msg.setUrl((char*)iter->sipId.c_str(),(char*)iter->addrIp.c_str(),iter->sipPort);

            pj_str_t from = pj_str(msg.FromHeader());
            pj_str_t to = pj_str(msg.ToHeader());
            pj_str_t requestUrl = pj_str(msg.RequestUrl());

            string method = "MESSAGE";
            pjsip_method reqMethod = {PJSIP_OTHER_METHOD,{(char*)method.c_str(),method.length()}};
            pjsip_tx_data* tdata;
            pj_status_t status = pjsip_endpt_create_request(GBOJ(gSipServer)->GetEndPoint(),&reqMethod,&requestUrl,&from,&to,NULL,NULL,-1,NULL,&tdata);
            if(PJ_SUCCESS != status)
            {
                LOG(ERROR)<<"pjsip_endpt_create_request ERROR";
                return;
            }
            tinyxml2::XMLElement* rootNode = parse.AddRootNode((char*)"Query");
            parse.InsertSubNode(rootNode,(char*)"CmdType",(char*)"Catalog");
            int sn = random() % 1024;
            char tmpStr[32] = {0};
            sprintf(tmpStr,"%d",sn);
            parse.InsertSubNode(rootNode,(char*)"SN",tmpStr);
            parse.InsertSubNode(rootNode,(char*)"DeviceID",iter->sipId.c_str());

            std::string xmlBuf;
            parse.getXmlData(xmlBuf);
            LOG(INFO) <<"xml: \n"<< xmlBuf;

            pj_str_t type = pj_str("Application");
            pj_str_t subtype = pj_str("MANSCDP+xml");
            pj_str_t xmldata = pj_str(const_cast<char*>(xmlBuf.data()));

            tdata->msg->body = pjsip_msg_body_create(tdata->pool,&type,&subtype,&xmldata);


            status = pjsip_endpt_send_request(GBOJ(gSipServer)->GetEndPoint(),tdata,-1,NULL,NULL);
            if(PJ_SUCCESS != status)
            {
                LOG(ERROR)<<"pjsip_endpt_send_request ERROR";
                return;
            }
        }
    }
    return;
}