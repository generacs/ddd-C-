#pragma once

#include "rtpsession.h"
#include "rtpsourcedata.h"
#include "rtptcptransmitter.h"
#include "rtptcpaddress.h"
#include "rtpudpv4transmitter.h"
#include "rtpipv4address.h"
#include "rtpsessionparams.h"
#include "rtperrors.h"
#include "rtplibraryversion.h"
#include "rtcpsrpacket.h"

#include "mpeg-ps.h"

#include <common.h>
#include <globalCtl.h>

#ifdef __cplusplus
extern "C"{
#endif
#include "jthread.h"
#ifdef __cplusplus
}
#endif

using namespace jrtplib;

typedef struct _PackProcStat
{
    _PackProcStat()
    {
        rSeq = -1;
        rTimeStamp = 0;
        rState = 1;
        rlen = 10*1024;
        rNow = 0;
        rBuf = (char*)malloc(rlen);
        unpackHnd = NULL;
        psFp = NULL;
        sCodec = 0;
        sBuf = (char*)malloc(rlen);
        slen = 10*1024;;
        sNow = 0;
        sKeyFrame = 0;
		sPts = 0;
		sFp = NULL;
		session = NULL;
    }
    ~_PackProcStat()
    {
        if(rBuf)
        {
            free(rBuf);
            rBuf = NULL;
        }
        if(psFp)
        {
            fclose(psFp);
            psFp = NULL;
        }
    }
    int rSeq;
    int rTimeStamp;
    int rState;
    int rlen;   //当前buf的总大小
    int rNow;   //当前已经收到的数据包大小
    char* rBuf;  //当前收取数据的buf
    char* sBuf;
    int slen;
    int sNow;
    void* unpackHnd;
    FILE* psFp;
    int sCodec;
    int sKeyFrame;
	int sPts;
	FILE* sFp;
	void* session;

}PackProcStat;


class Gb28181Session : public RTPSession,public Session
{
    public:
        Gb28181Session(const DeviceInfo& devInfo) : Session(devInfo){
            
        }
        ~Gb28181Session(){}

        int CreateRtpSession(string dstip,int dstport){
            LOG(INFO) << "CreateRtpSession";
            RTPSessionParams sessParams;
            sessParams.SetOwnTimestampUnit(1.0/90000.0);
            sessParams.SetAcceptOwnPackets(true);
            sessParams.SetUsePollThread(true);
            sessParams.SetNeedThreadSafety(true);
            sessParams.SetMinimumRTCPTransmissionInterval(RTPTime(5,0));
            int ret = -1;
            if(1)
            {

                RTPUDPv4TransmissionParams transparams;
                transparams.SetRTPReceiveBuffer(1024*1024);
                transparams.SetPortbase(2000);
                
                ret = Create(sessParams,&transparams);
                // ret = Create(sessParams,&transparams);
                LOG(INFO)<<"ret:"<<ret;
                if(ret < 0)
                {
                    LOG(ERROR)<<"udp create fail";
                }
                else
                {
                    LOG(INFO)<<"udp create ok,bind:"<<rtp_loaclport;
                }
            }
            else
            {
                sessParams.SetMaximumPacketSize(65535);
                RTPTCPTransmissionParams transParams;
                ret = Create(sessParams, &transParams, RTPTransmitter::TCPProto);
                if(ret < 0)
                {
                    // LOG(ERROR) << "Rtp tcp error: " << RTPGetErrorString(ret);
                    return -1;
                }

                //会话创建成功后，接下来需要创建tcp连接
                int sessFd = RtpTcpInit(dstip,dstport,5);
                LOG(INFO)<<"sessFd:"<<sessFd;
                if(sessFd < 0)
                {
                    LOG(ERROR)<<"RtpTcpInit faild";
                    return -1;
                }
                else
                {
                    AddDestination(RTPTCPAddress(sessFd));
                }
            }
            

            return ret;
        }
        int RtpTcpInit(string dstip,int dstport,int time){
            LOG(INFO) << "RtpTcpInit";
        }
		int SendPacket(int media,char* data,int datalen,int codecId){
            LOG(INFO) << "SendPacket";
        }
    protected:
        enum
        {
            RtpPack_FrameContinue = 0,
            RtpPack_FrameCurFinsh,
            RtpPack_FrameNextStart,
        };
        void OnPollThreadStep(){
            LOG(INFO) << "OnPollThreadStep";
        }
        void ProcessRTPPacket(RTPSourceData& srcdat,RTPPacket& pack){
            LOG(INFO) << "ProcessRTPPacket";
        }
        void OnRTPPacketProcPs(int mark,int curSeq,int timestamp,unsigned char* payloadData,int payloadLen){
            
            LOG(INFO) << "OnRTPPacketProcPs";
        }
        void OnNewSource(RTPSourceData *srcdat)
        {
           			LOG(INFO)<<"OnNewSource";
			LOG(INFO)<<"srcdat->IsOwnSSRC():"<<srcdat->IsOwnSSRC();
            if(srcdat->IsOwnSSRC())
                return;
            
            uint32_t ip;
            uint16_t port;
			LOG(INFO)<<"00";
            if(srcdat->GetRTPDataAddress() != 0)
            {
				LOG(INFO)<<"11";
                const RTPIPv4Address* addr = (const RTPIPv4Address*)srcdat->GetRTPDataAddress();
                ip = addr->GetIP();
                port = addr->GetPort();
            }
            else if(srcdat->GetRTCPDataAddress() != 0)
            {
				LOG(INFO)<<"22";
                const RTPIPv4Address* addr = (const RTPIPv4Address*)srcdat->GetRTCPDataAddress();
                ip = addr->GetIP();
                port = addr->GetPort()-1;
            }
            else
			{
				LOG(INFO)<<"33";
				return;
			}
                
            
            RTPIPv4Address dest(ip,port);
            AddDestination(dest);
            struct in_addr inaddr;
            inaddr.s_addr = htonl(ip);
            LOG(INFO)<<"Adding destination "<<string(inet_ntoa(inaddr))<<":"<<port;
        }

        void OnRemoveSource(RTPSourceData *srcdat)
        {
            LOG(INFO) << "OnRemoveSource";
        }

        void OnBYEPacket(RTPSourceData *srcdat)
        {
            LOG(INFO) << "OnBYEPacket" ;
        }

    private:
        PackProcStat* m_proc;
		int m_count;
        int m_rtpTcpFd;
        int m_listenFd;
};
