#include <iostream>
#include "check.hpp"
using namespace std;
int main()
{
    std::cout << "-------------------系统信息--------------------" << std::endl; 
    std::cout << "CPU 型号          :" << getProcessorInfo << std::endl;
    std::cout << "CPU 频率          :" << getProcessorgfrep << std::endl;
    std::cout << "CPU 缓存          :" << getProcessorgCache << std::endl;
    std::cout << "硬盘空间          :" << getDiskSize << std::endl;
} // namespace std;
