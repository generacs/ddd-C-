#include <iostream>
#include <memory>
#include <thread>
#include <sip.h>

int main(int argc, char** argv){
    std::cout << "hello world" << std::endl;

    std::unique_ptr<SipCore> sipPtr = std::make_unique<SipCore>();
    sipPtr->InitSip(10086);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
    
    return 0;
}