#pragma once

#include <taskTimer.h>
#include <common.h>

class OpenStream
{
    public:
        OpenStream();
        ~OpenStream();

        void StreamServiceStart();
        static void StreamGetProc(void* param);
		static void CheckSession(void* param){
            LOG(INFO) << "CheckSession";
        }
		static void StreamStop(string platformId, string devId){
            LOG(INFO) << "StreamStop";
        }
    private:
        TaskTimer* m_pStreamTimer;
        TaskTimer* m_pCheckSessionTimer;
};
