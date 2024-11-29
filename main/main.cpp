#include <iostream>
#include <memory>
#include <thread>
#include <sip.h>
#include <common.h>


#include <sipLocalConfig.h>

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

int main(int argc, char** argv){

    test002();
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
    
    return 0;
}