#include <iostream>
#include <memory>
#include <thread>
#include <sip.h>
#include <common.h>

#include <sipLocalConfig.h>
#include <globalCtl.h>

void test001(){
    std::cout << "hello world" << std::endl;

    std::unique_ptr<SipCore> sipPtr = std::make_unique<SipCore>();
    sipPtr->InitSip(10086);

}
void test002(){
    std::unique_ptr<SipLocalConfig> config = std::make_unique<SipLocalConfig>();
    int ret = config->ReadConf();
    if(ret == -1)
	{
		LOG(ERROR)<<"read config error";
		return;
	}
    return;
}
void test003(){
    std::shared_ptr<SipLocalConfig> config = std::make_shared<SipLocalConfig>();
	int ret = config->ReadConf(); 
	if(ret == -1)
	{
		LOG(ERROR)<<"read config error";
		return ;
	}
	bool re = GlobalCtl::instance()->init(config);
	if(re == false)
	{
		LOG(ERROR)<<"init error";
		return;
	}
	LOG(INFO)<<GBOJ(gConfig)->localIp();
}


int main(int argc, char** argv){
    test003();
    
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
    
    return 0;
}