#include <iostream>
#include "check.hpp"
#include "membench.hpp"

extern "C"
using namespace std;
int main()
{
    std::cout << "-------------------系统信息--------------------" << std::endl;
    std::cout << "CPU 型号          : " << getCPUModel() << std::endl;
    std::cout << "CPU 核心数        : " << getCPUCores() << std::endl;
    std::cout << "CPU 频率          : " << getCPUFrequency() << std::endl;
    std::cout << "CPU 缓存          : " << "L1:" << getCPUCacheL1() << "K L2:" 
            << getCPUCacheL2() << "K L3:" << getCPUCacheL3() << "K" << std::endl;
    std::cout << "硬盘空间          : " << formatSize(getDiskTotalSpace("/")) << " ("
            << formatSize(getDiskUsedSpace("/")) << " 可用空间)" << std::endl;
    std::cout << "内存              : " << formatSize(getMemoryTotal()) << " ("
            << formatSize(getMemoryUsed()) << " 可用内存)" << std::endl;
    std::cout << "SWAP              : " << formatSize(getSwapTotal()) << " ("
            << formatSize(getSwapUsed()) << " 可用SWAP)" << std::endl;
    std::cout << "系统              : " << getSystemVersion() << std::endl;

    // std::cout << "------------------内存测试--------------------" << std::endl;
    // std::cout << "内存测试 Test (Fast Mode, 1-Pass @ 5sec)" << std::endl;
    // std::cout << "单线程读测试:\t\t" << getWriteSpeed() << " MB/s" << std::endl;
    // std::cout << "单线程写测试:\t\t" <<  << " MB/s" << std::endl;

} // namespace std;
