#pragma once
#include <common.h>



class SipMessage
{
    public:
        SipMessage();
        ~SipMessage();
    
    public:
        void setFrom(char* fromUsr,char* fromIp);
        void setTo(char* toUsr,char* toIp);
        void setUrl(char* sipId,char* url_ip,int url_port,char* url_proto = (char*)"tcp");
        void setContact(char* sipId,char* natIp,int natPort);

        inline char* FromHeader(){return fromHeader;}
        inline char* ToHeader(){return toHeader;}
        inline char* RequestUrl(){return requestUrl;}
        inline char* Contact(){return contact;}

    private:
        char fromHeader[128];
        char toHeader[128];
        char requestUrl[128];
        char contact[128];
};