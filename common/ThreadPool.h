#pragma once
#include <common.h>
#include <queue>
#include "ECThread.h"

class ThreadTask
{
    public:
        ThreadTask(){}
        virtual ~ThreadTask(){}
        virtual void run()=0;
};


class ThreadPool
{
    public:
        ThreadPool();
        ~ThreadPool();

        int createThreadPool(int threadCount);
        int waitTask();
        int postTask(ThreadTask* task);

        static void* mainThread(void* argc);
        static queue<ThreadTask*> m_taskQueue;
        static pthread_mutex_t m_queueLock;
    private:
        sem_t m_signalSem;
};