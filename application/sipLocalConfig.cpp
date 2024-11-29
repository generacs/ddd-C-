#include "sipLocalConfig.h"

#define CONFIGFILE_PATH "../../../../../conf/SipSupService.conf"
#define LOCAL_SECTION "localserver"
#define SIP_SECTION "sipserver"

static const string keyLocalIp = "local_ip";
static const string keyLocalPort = "local_port";
static const string keySipId = "sip_id";
static const string keySipIp = "sip_ip";
static const string keySipPort = "sip_port";
static const string keySipRealm = "sip_realm";
static const string keySipUsr = "sip_usr";
static const string keySipPwd = "sip_pwd";
static const std::string keyRtpPortBegin   = "rtp_port_begin";
static const std::string keyRtpPortEnd   = "rtp_port_end";

static const string keySubNodeNum = "subnode_num";
static const string keySubNodeId = "sip_subnode_id";
static const string keySubNodeIp = "sip_subnode_ip";
static const string keySubNodePort = "sip_subnode_port";
static const string keySubNodePoto = "sip_subnode_poto";
static const string keySubNodeAuth = "sip_subnode_auth";

SipLocalConfig::SipLocalConfig()
:m_conf(CONFIGFILE_PATH)
{
    m_localIp = "";
    m_localPort = 0;
    m_sipId = "";
    m_sipIp = "";
    m_sipPort = 0;
    m_sipRealm = "";
    m_subNodeIp = "";
    m_subNodePort = 0;
    m_subNodePoto = 0;
    m_subNodeAuth = 0;
}
SipLocalConfig::~SipLocalConfig()
{

}

int SipLocalConfig::ReadConf()
{
    int ret = 0;
    m_conf.setSection(LOCAL_SECTION);
    m_localIp = m_conf.readStr(keyLocalIp);
    if(m_localIp.empty())
    {
        ret = -1;
        LOG(ERROR)<<"localIp is wrong";
        return ret;
    }
    m_localPort = m_conf.readInt(keyLocalPort);
    if(m_localPort <= 0)
    {
        ret = -1;
        LOG(ERROR)<<"localPort is wrong";
        return ret;
    }

    m_conf.setSection(SIP_SECTION);
    m_sipId = m_conf.readStr(keySipId);
    if(m_sipId.empty())
    {
        ret = -1;
        LOG(ERROR)<<"sipId is wrong";
        return ret;
    }

    m_sipIp = m_conf.readStr(keySipIp);
    if(m_sipIp.empty())
    {
        ret = -1;
        LOG(ERROR)<<"sipIp is wrong";
        return ret;
    }
    m_sipPort = m_conf.readInt(keySipPort);
    if(m_sipPort <= 0)
    {
        ret = -1;
        LOG(ERROR)<<"sipPort is wrong";
        return ret;
    }

    m_sipRealm = m_conf.readStr(keySipRealm);
    if(m_sipRealm.empty())
    {
        ret = -1;
        LOG(ERROR)<<"sipRealm is wrong";
        return ret;
    }

    m_usr = m_conf.readStr(keySipUsr);
    if(m_usr.empty())
    {
        ret = -1;
        LOG(ERROR)<<"usr is wrong";
        return ret;
    }

    m_pwd = m_conf.readStr(keySipPwd);
    if(m_pwd.empty())
    {
        ret = -1;
        LOG(ERROR)<<"pwd is wrong";
        return ret;
    }
    LOG(INFO)<<"localip:"<<m_localIp<<",localport:"<<m_localPort<<",sipid:"<<m_sipId<<",sipip:"<<m_sipIp\
    <<",sipport:"<<m_sipPort<<",sipRealm"<<m_sipRealm;
	
	m_rtpPortBegin = m_conf.readInt(keyRtpPortBegin);
    if(m_rtpPortBegin<=0)
    {
       ret =-1;
       LOG(ERROR)<<"rtpPortBegin is NULL";
       return ret;
    }

    m_rtpPortEnd = m_conf.readInt(keyRtpPortEnd);
    if(m_rtpPortEnd<=0)
    {
       ret =-1;
       LOG(ERROR)<<"rtpPortEnd is NULL";
       return ret;
    }
	initRandPort();
	
    int num = m_conf.readInt(keySubNodeNum);
    LOG(INFO)<<"num:"<<num;
    SubNodeInfo info;
    for(int i = 1;i<num+1;++i)
    {
        string id = keySubNodeId + to_string(i);
        string ip = keySubNodeIp + to_string(i);
        string port = keySubNodePort + to_string(i);
        string poto = keySubNodePoto + to_string(i);
        string auth = keySubNodeAuth + to_string(i);

        info.id = m_conf.readStr(id);
        info.ip = m_conf.readStr(ip);
        info.port = m_conf.readInt(port);
        info.poto = m_conf.readInt(poto);
        info.auth = m_conf.readInt(auth);
        ubNodeInfoList.push_back(info);
    }
    LOG(INFO)<<"ubNodeInfoList.SIZE:"<<ubNodeInfoList.size();


    return ret;
}

void SipLocalConfig::initRandPort()
{
    
    while(m_rtpPortBegin % 2)  
    {
        m_rtpPortBegin++;
    }


    while(m_rtpPortEnd % 2 == 0)
    {
        m_rtpPortEnd--;
    }

    
    AutoMutexLock lck(&m_rtpPortLock);
    for(int i=m_rtpPortBegin;i< (m_rtpPortEnd + 1);i++)
    {
        m_RandNum.push(i);
    }
    LOG(INFO)<<"rand size:"<<m_RandNum.size();
}


int SipLocalConfig::popOneRandNum()
{
    int rtpPort = 0;
    AutoMutexLock lck(&m_rtpPortLock);
    if(m_RandNum.size()>0)
    {
        //取完一个就扔出队列，每次取两个号
        rtpPort = m_RandNum.front();
        m_RandNum.pop();
        if(rtpPort % 2) //这里我们再做下判断
        {
            //如果第一个是奇数，那么重新取
            rtpPort = m_RandNum.front();
            m_RandNum.pop();
        }
        //取第二个号
        m_RandNum.pop();
    }
    return rtpPort;
}

//回收rtp port
int SipLocalConfig::pushOneRandNum(int num)
{
    if(num < m_rtpPortBegin || num > m_rtpPortEnd)
    {
        return -1;
    }
    AutoMutexLock lck(&m_rtpPortLock);
    m_RandNum.push(num);
    m_RandNum.push(num+1);
	LOG(INFO)<<"push rtp:"<<num<<",rtcp:"<<num+1;
	return 0;
}