#include <iostream>
#include <memory>
#include <thread>
#include <sip.h>
#include <common.h>

#include <sipLocalConfig.h>
#include <globalCtl.h>
#include <sipCatalog.h>
#include <sipStream.h>


void test001(){
    std::cout << "hello world" << std::endl;

    // std::unique_ptr<SipCore> sipPtr = std::make_unique<SipCore>();
	std::unique_ptr<SipCore> sipPtr(new SipCore);
    sipPtr->InitSip(10086);

}
void test002(){
    // std::unique_ptr<SipLocalConfig> config = std::make_unique<SipLocalConfig>();
    std::unique_ptr<SipLocalConfig> config(new SipLocalConfig);
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

	std::this_thread::sleep_for(std::chrono::seconds(10));
	
	SipCatalog log;
	std::this_thread::sleep_for(std::chrono::seconds(10));

	


}


int main(int argc, char** argv){
    test003();

	std::shared_ptr<OpenStream> gbStreamPtr = std::make_shared<OpenStream>();
	gbStreamPtr->StreamServiceStart(); 
	
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
    
    return 0;
}