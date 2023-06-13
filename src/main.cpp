#include <iostream>
#include "check.hpp"
#include "cpubench.hpp"
using namespace std;
int main()
{
    std::cout << "-------------------系统信息--------------------" << std::endl; 
    std::cout << "CPU 型号          :" << getProcessorInfo << std::endl;
    std::cout << "CPU 频率          :" << getProcessorgfrep << std::endl;
    std::cout << "CPU 缓存          :" << getProcessorgCache << std::endl;
    std::cout << "硬盘空间          :" << getDiskSize << std::endl;
    std::cout << "-------------------性能测试--------------------" << std::endl; 
    double multiCoreResult = performMultiCoreBenchmark();
    std::cout << "CPU多核成绩       :" << multiCoreResult << std::endl;
    double singleCoreResult = performSingleCoreBenchmark();
    std::cout << "CPU单核成绩       :" << singleCoreResult << std::endl;

} // namespace std;
