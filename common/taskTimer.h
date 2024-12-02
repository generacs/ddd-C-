#pragma once

#include <unistd.h>
#include <sys/time.h>

typedef void (*timerCallBack)(void* param);
class TaskTimer
{
    public:
        TaskTimer(int timeSecond);
        ~TaskTimer();

        void start();
        void stop();

        void setTimerFun(timerCallBack fun,void* param);

        static void* timer(void* context);
    private:
        timerCallBack m_timerFun;
        void* m_funParam;
        int m_timeSecond;
        bool m_timerStop;
};