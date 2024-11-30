#pragma once

#include <pthread.h>
#include <string>
#include <sys/prctl.h>

namespace EC
{
    typedef void* (*ECThreadFunc)(void*);
    class ECThread
    {
        public:
            static int createThread(ECThreadFunc startRoutine,void* args,pthread_t& id);
            static int detachSelf();
            static void exitSelf(void* rval);
            static int waitThread(const pthread_t& id);
            static int terminateThread(const pthread_t& id);
        private:
            ECThread(){}
            ~ECThread(){}
    };
}

