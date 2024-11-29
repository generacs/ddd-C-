#pragma once

#include <glog/logging.h>

#include "tinyxml2.h"
#include <json/json.h>

#include <json/json.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <memory>
#include <sstream>
using namespace std;

#define LOG_DIR "/mnt/hgfs/share/log"
#define LOG_FILE_NAME "SipServer.log"

class AutoMutexLock
{
    public:
        AutoMutexLock(pthread_mutex_t* l):lock(l)
        {
            LOG(INFO)<<"getLock";
            getLock();
        };
        ~AutoMutexLock()
        {
            LOG(INFO)<<"freeLocak";
            freeLocak();
        };
    private:
        AutoMutexLock();
        AutoMutexLock(const AutoMutexLock&);
        AutoMutexLock& operator=(const AutoMutexLock&);
        void getLock(){pthread_mutex_lock(lock);}
        void freeLocak(){pthread_mutex_unlock(lock);}
        pthread_mutex_t* lock;
};

class JsonParse
{
    public:
        JsonParse(string s)
        :m_str(s){}

        JsonParse(Json::Value j)
        :m_json(j){}

        bool toJson(Json::Value& j)
        {
            bool bret = false;
            Json::CharReaderBuilder builder;
            Json::CharReaderBuilder::strictMode(&builder.settings_);
            builder["collectComents"] = true;

            const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

            JSONCPP_STRING errs;
            bret = reader->parse(m_str.data(),m_str.data()+m_str.size(),&j,&errs);
            if(!bret || !errs.empty())
            {
                LOG(ERROR)<<"json parse error:"<<errs.c_str();
            }

            return bret;

        }

        string toString()
        {
            Json::StreamWriterBuilder builder;
            char* indent="";
            builder["indentation"] = indent;
            return Json::writeString(builder,m_json);
        }

    private:
        string m_str;
        Json::Value m_json;

};
