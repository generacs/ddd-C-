#include "sipDirectory.h"
#include <sipDef.h>
#include <globalCtl.h>

SipDirectory::SipDirectory(tinyxml2::XMLElement* root)
    :SipTaskBase()
{
    m_pRootElement = root;
}

SipDirectory::~SipDirectory()
{

}

pj_status_t SipDirectory::run(pjsip_rx_data *rdata)
{
    int status_code = SIP_SUCCESS;
    //解析message-body-xml数据
    // SaveDir(status_code);
    //响应
    pj_status_t status = pjsip_endpt_respond(GBOJ(gSipServer)->GetEndPoint(),NULL,rdata,status_code,NULL,NULL,NULL,NULL);
    if(PJ_SUCCESS != status)
    {
        LOG(ERROR)<<"pjsip_endpt_respond error";
    }

    return status;
}

void SipDirectory::SaveDir(int& status_code)
{
    tinyxml2::XMLElement* pRootElement = m_pRootElement;
    if(!pRootElement)
    {
        status_code = SIP_BADREQUEST;
        return;
    }

    string strCenterDeviceID,strSumNum,strSn,strDeviceID,strName,strManufacturer,
    strModel,strOwner,strCivilCode,strParental,strParentID,strSafetyWay,
    strRegisterWay,strSecrecy,strStatus;
    
    tinyxml2::XMLElement* pElement = pRootElement->FirstChildElement("DeviceID");
    if(pElement && pElement->GetText())
        strCenterDeviceID = pElement->GetText();
    std::cout << "strCenterDeviceID = " << strCenterDeviceID << std::endl;
    if(!GlobalCtl::checkIsVaild(strCenterDeviceID))
    {
        status_code = SIP_BADREQUEST;
        return;
    }
    
    pElement = pRootElement->FirstChildElement("SumNum");
    if(pElement && pElement->GetText())
        strSumNum = pElement->GetText();

    pElement = pRootElement->FirstChildElement("SN");
    if(pElement && pElement->GetText())
        strSn = pElement->GetText();


    pElement = pRootElement->FirstChildElement("DeviceList");
    if(pElement)
    {
        tinyxml2::XMLElement* pItem = pElement->FirstChildElement("item");
        while(pItem)
        {
            tinyxml2::XMLElement* pChild = pItem->FirstChildElement("DeviceID");
            if(pChild && pChild->GetText())
            {
                strDeviceID = pChild->GetText();
                std::cout << "strDeviceID = " << strDeviceID << std::endl;
                if(strDeviceID.length() == 20)
                {
                    DevTypeCode type = GlobalCtl::getSipDevInfo(strDeviceID);
                    if(type == Camera_Code || type == Ipc_Code)
                    {
                        GlobalCtl::gRcvIpc = true;
                        LOG(INFO)<<"get ipc device";
                    }
                }
            }
                
            


            pChild = pItem->FirstChildElement("Name");
            if(pChild && pChild->GetText())
                strName = pChild->GetText();
            std::cout << "strName" << std::endl;
            pChild = pItem->FirstChildElement("Manufacturer");
            if(pChild && pChild->GetText())
                strManufacturer = pChild->GetText();
            
            pChild = pItem->FirstChildElement("Model");
            if(pChild && pChild->GetText())
                strModel = pChild->GetText();

            pChild = pItem->FirstChildElement("Owner");
            if(pChild && pChild->GetText())
                strOwner = pChild->GetText();

            pChild = pItem->FirstChildElement("CivilCode");
            if(pChild && pChild->GetText())
                strCivilCode = pChild->GetText();

            pChild = pItem->FirstChildElement("Parental");
            if(pChild && pChild->GetText())
                strParental = pChild->GetText();

            pChild = pItem->FirstChildElement("ParentID");
            if(pChild && pChild->GetText())
                strParentID = pChild->GetText();

            pChild = pItem->FirstChildElement("SafetyWay");
            if(pChild && pChild->GetText())
                strSafetyWay = pChild->GetText();

            pChild = pItem->FirstChildElement("RegisterWay");
            if(pChild && pChild->GetText())
                strRegisterWay = pChild->GetText();
            
            pChild = pItem->FirstChildElement("Secrecy");
            if(pChild && pChild->GetText())
                strSecrecy = pChild->GetText();
            
            pChild = pItem->FirstChildElement("Status");
            if(pChild && pChild->GetText())
                strStatus = pChild->GetText();

            pItem = pItem->NextSiblingElement();
        }

    }
}