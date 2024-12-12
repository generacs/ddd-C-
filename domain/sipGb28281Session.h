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
#include <fstream>

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
class Gb28181Session;
//需要用codecid来判别裸流是音频还是视频数据
//stream 流的编号  用不上
//flags 视频关键帧的标识
static void ps_demux_callback(void* param, int stream, int codecid, int flags, int64_t pts, int64_t dts, const void* data, size_t bytes)
{
    
	PackProcStat* pProc = (PackProcStat*)param;
    //然后需要在结构体里再添加几个成员

    //数据流类型(音/视频)
    int media = -1;
    //视频帧类型(I/P帧)
    int frameType = 1;
    
    //我们先判别下当前的codecid是否有效
	if(codecid == 0) // unknown codec id
	{
		return;
	}
	
    //首先先处理同一类型的流数据被拆成多个包的情况
    //当前回调被第一次调用时，不会走这个逻辑
	if(pProc->sCodec == codecid && pProc->sPts == pts)
	{
        //我们需要将当前的裸流保存到buffer，后续我们再处理buffer的数据
		if(pProc->slen < pProc->sNow + (int)bytes)
		{
			pProc->slen = pProc->sNow + (int)bytes + 1024;
			pProc->sBuf = (char *)realloc(pProc->sBuf, pProc->slen);
		}
		memcpy(pProc->sBuf + pProc->sNow, data, bytes);
		pProc->sNow += bytes;
		pProc->sKeyFrame = flags;
		return;
	}

    //当前这个接口第一次调用时，会走这个逻辑
    //后续这个逻辑是来处理当前传入的data为下一帧数据或者不同类型的数据，
	else 
	{
		//如果发送buffer的数据大于0，那么我们就进行发送，发送前还需要进行header的设定，一会我们再做
		if(pProc->sNow > 0)
		{
			do{
				if(pProc->sCodec == STREAM_VIDEO_H264
					|| pProc->sCodec == STREAM_VIDEO_H265)
				{
                    //在这里可以先区分媒体流的类型，和当前视频帧是否为关键帧
					media = 2;
					//frameType = pProc->sKeyFrame > 1 ? FORMAT_VIDEO_I : FORMAT_VIDEO_P;
#if 1
					if(pProc->sFp == NULL)
					{
						pProc->sFp = fopen("/home/zengyao/conf/send.h264", "w+");
					}

					if(pProc->sFp != NULL)
					{
						fwrite(pProc->sBuf, 1, pProc->sNow, pProc->sFp);
					}
#endif
				}
				else if(pProc->sCodec == STREAM_AUDIO_AAC
						|| pProc->sCodec == STREAM_AUDIO_G711
						|| pProc->sCodec == STREAM_AUDIO_G711U)
				{
					media = 1;
				}
				else
				{
				// 	if(pProc->unknownCodecCnt == 0)
				// 		LOG(INFO) << " unknown codec: " << pProc->sCodec;

				// 	if(pProc->unknownCodecCnt ++ > 200)
				// 		pProc->unknownCodecCnt = 0;

					break;
				}

				//unsigned long long microsecIn = pProc->sDts * 1000 / 90000;
                // Gb28181Session* pGbSesson = (Gb28181Session*)pProc->session;
				// int sendLen = pGbSesson->SendPacket(media, (char *)pProc->sBuf, pProc->sNow, pProc->sCodec);
			}while(0);
		}
		//LOG(INFO)<<"33333333";
		// copy new data to send buffer
		pProc->sNow = 0;
		pProc->sKeyFrame = 0;
        //将当前数据copy到buffer中
		if(pProc->slen < pProc->sNow + (int)bytes)
		{
			pProc->slen = pProc->sNow + bytes + 1024;
			pProc->sBuf = (char *)realloc(pProc->sBuf, pProc->slen);
		}
		memcpy(pProc->sBuf + pProc->sNow, data, bytes);
		pProc->sNow += bytes;
		pProc->sKeyFrame = flags;

		pProc->sPts = pts;
		
		pProc->sCodec = codecid;
	}

	return;
}
class Gb28181Session : public RTPSession,public Session
{
    public:
        Gb28181Session(const DeviceInfo& devInfo) : Session(devInfo){
            m_proc = std::make_shared<PackProcStat>();
            
            m_logFile.open("test.ps", ios::out | ios::binary | ios::app);
        }
        ~Gb28181Session(){
            m_logFile.close();
        }

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
                transparams.SetPortbase(rtp_loaclport);
                
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
            
            BeginDataAccess();

            if(GotoFirstSourceWithData())
            {
                do
                {
                    RTPSourceData* srcdat = NULL;
                    RTPPacket* pack = NULL;
                    srcdat = GetCurrentSourceInfo();
                    while((pack = GetNextPacket()) != NULL)
                    {
                        //
                        
                        ProcessRTPPacket(*srcdat,*pack);

                        DeletePacket(pack);
                    }

                } while (GotoNextSourceWithData());  
            }
            EndDataAccess();

        }
        void ProcessRTPPacket(RTPSourceData& srcdat,RTPPacket& pack){

            int payloadType = pack.GetPayloadType();
            int payloadLen = pack.GetPayloadLength();
            int mark = pack.HasMarker();
            int curSeq = pack.GetExtendedSequenceNumber();
            int timestamp = pack.GetTimestamp();
            unsigned char* payloadData = pack.GetPayloadData();
            LOG(INFO) << "curSeq" << curSeq << " timestamp:" << timestamp;
            if(payloadType != 96  && payloadType != 98)
            {
                LOG(ERROR)<<"rtp unknown payload type:"<<payloadType;
                return;
            }
            //在这里更新下下级最后有rtp包推送的时间
            gettimeofday(&m_curTime, NULL);
            //那么就在接收rtp包的时机给这个session进行赋值
            //这里需要先判断下
            if(m_proc && m_proc->session == NULL)
            {
                m_proc->session = (void*)this;
            }


            if(payloadType == 96)
            {
                OnRTPPacketProcPs(mark,curSeq,timestamp,payloadData,payloadLen);
            }
            else if(payloadType == 98)
            {

            }

        }
        void OnRTPPacketProcPs(int mark,int curSeq,int timestamp,unsigned char* payloadData,int payloadLen){

                int FrameStat = mark;

                if(m_proc->rSeq == -1)
                    m_proc->rSeq = curSeq;

                if(m_proc->rTimeStamp == 0)
                    m_proc->rTimeStamp = timestamp;

                if(curSeq - m_proc->rSeq > 1)
                {
                    m_proc->rState = 2;
                    LOG(ERROR)<<"rtp drop pack diff:"<<curSeq - m_proc->rSeq;
                }


                if(FrameStat == 0)
                {
                    // LOG(INFO)<<"m_proc->rTimeStamp:"<<m_proc->rTimeStamp"<< timestamp:"<<timestamp;
                    
                    if(timestamp != m_proc->rTimeStamp)
                    {
                        FrameStat = RtpPack_FrameNextStart;
                    }
                }

                m_proc->rSeq = curSeq;
                m_proc->rTimeStamp = timestamp;

                if(m_proc->rState == 1)
                {
                    if(FrameStat == RtpPack_FrameContinue || FrameStat == RtpPack_FrameCurFinsh)
                    {
                        if(m_proc->rlen < payloadLen + m_proc->rNow)
                        {
                            m_proc->rlen = payloadLen + m_proc->rNow + 1024;
                            m_proc->rBuf = (char*)realloc(m_proc->rBuf,m_proc->rlen);
                        }
                        memcpy(m_proc->rBuf + m_proc->rNow,payloadData,payloadLen);
                        m_proc->rNow += payloadLen;
                    }
                }
                else if(m_proc->rState == 2)
                {
                    m_proc->rState = 1;

                    memset(m_proc->rBuf,0,m_proc->rNow);
                    m_proc->rNow = 0;
                    m_proc->rSeq = -1;
                    m_proc->rTimeStamp = 0;

                    if(FrameStat == RtpPack_FrameNextStart)
                    {
                        if(m_proc->rlen < payloadLen + m_proc->rNow)
                        {
                            m_proc->rlen = payloadLen + m_proc->rNow + 1024;
                            m_proc->rBuf = (char*)realloc(m_proc->rBuf,m_proc->rlen);
                        }
                        memcpy(m_proc->rBuf + m_proc->rNow,payloadData,payloadLen);
                        m_proc->rNow += payloadLen;
                    }
                    return;
                    
                }
                if(FrameStat)
                {
                    if(m_proc->psFp == NULL)
                    {
                        m_proc->psFp = fopen("data.ps","w+");
                    }
                    if(m_proc->psFp)
                    {
                        fwrite(m_proc->rBuf,1,m_proc->rNow,m_proc->psFp);
                    }
                    //ps demutex
                    if(m_proc->unpackHnd == NULL)
                    {
                        LOG(INFO)<<"ps_demuxer_create";
                        //这里需要定义一个回调接口，用来接收处理的解封装后的音视频数据
                        m_proc->unpackHnd = (void *)ps_demuxer_create((ps_dumuxer_onpacket)ps_demux_callback, (void *)m_proc.get());
                    }

                    if(m_proc->unpackHnd)
                    {
                        //LOG(INFO)<<"PS SIZE:"<<m_proc->rNow;
                        int offset = 0;
                        while(offset < m_proc->rNow)
                        {
                            //这里需将缓存的数据传入到ps解封装接口中，
                            int ret = ps_demuxer_input((struct ps_demuxer_t *)m_proc->unpackHnd, (const uint8_t*)m_proc->rBuf+offset , m_proc->rNow-offset);
                            if(ret == 0)
                            {
                                LOG(ERROR) << "wrong payload data !!!!! can't demux the PS data";
                            }
                            offset += ret;
                        }
                        
                    }


                    memset(m_proc->rBuf,0,m_proc->rNow);
                    m_proc->rNow = 0;

                    if(FrameStat == RtpPack_FrameNextStart)
                    {
                        if(m_proc->rlen < payloadLen + m_proc->rNow)
                        {
                            m_proc->rlen = payloadLen + m_proc->rNow + 1024;
                            m_proc->rBuf = (char*)realloc(m_proc->rBuf,m_proc->rlen);
                        }
                        memcpy(m_proc->rBuf + m_proc->rNow,payloadData,payloadLen);
                        m_proc->rNow += payloadLen;
                    }

                }

                return;
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
        std::shared_ptr<PackProcStat> m_proc;
		int m_count;
        int m_rtpTcpFd;
        int m_listenFd;

        // 
        std::ofstream m_logFile;

};
