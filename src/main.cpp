#include <iostream>
#include "check.hpp"
// #include "sysbench/src/sysbench.h"
#include "membench.hpp"
extern "C"
using namespace std;
int main()
{
std::cout << "-------------------系统信息--------------------" << std::endl;
std::cout << "CPU 型号          : " << getCPUModel() << std::endl;
std::cout << "CPU 核心数        : " << getCPUCores() << std::endl;
std::cout << "CPU 频率          : " << getCPUFrequency() << std::endl;
std::cout << "CPU 缓存          : " << getCPUCache() << std::endl;
std::cout << "硬盘空间          : " << formatSize(getDiskTotalSpace("/")) << " ("
          << formatSize(getDiskUsedSpace("/")) << " 可用空间)" << std::endl;
std::cout << "内存              : " << formatSize(getMemoryTotal()) << " ("
          << formatSize(getMemoryUsed()) << " 可用内存)" << std::endl;
std::cout << "SWAP              : " << formatSize(getSwapTotal()) << " ("
          << formatSize(getSwapUsed()) << " 可用SWAP)" << std::endl;
std::cout << "系统              : " << getSystemVersion() << std::endl;


sysbench_init(NULL);
sysbench_opt_set_num_threads(8); //线程数
sysbench_opt_set_max_requests(1000000); //请求数
sysbench_opt_set_memory_block_size(1<<20); //内存块大小
int rc;
rc = sysbench_run_test("memory", "sequential", NULL, NULL); //顺序读写内存

rc = sysbench_run_test("cpu", "prime", NULL, NULL); //CPU测试
printf("Memory test result: \n");
sysbench_print_results("memory");

printf("CPU test result: \n");  
sysbench_print_results("cpu");
sysbench_cleanup();
    // std::cout << "-------------------性能测试--------------------" << std::endl; 
    // double multiCoreResult = performMultiCoreBenchmark();
    // std::cout << "CPU多核成绩       :" << multiCoreResult << std::endl;
    // double singleCoreResult = performSingleCoreBenchmark();
    // std::cout << "CPU单核成绩       :" << singleCoreResult << std::endl;
    // //-------------------内存测试--------------------
    // int dataSize = 1000000; // 数据大小（以整数为单位）

    // // 分配内存并初始化数据
    // __uint128_t* data = new __uint128_t[dataSize];
    // std::memset(data, 0, dataSize * sizeof(__uint128_t));

    // // 测试内存读性能并返回结果
    // double readResult = testMemoryReadPerformance(data, dataSize);
    // std::cout << "------------------内存测试--------------------" << std::endl;
    // std::cout << "内存测试 Test (Fast Mode, 1-Pass @ 5sec)" << std::endl;
    // std::cout << "单线程读测试:\t\t" << std::fixed << std::setprecision(2) << readResult << " MB/s" << std::endl;

    // // 测试内存写性能并返回结果
    // double writeResult = testMemoryWritePerformance(data, dataSize);
    // std::cout << "单线程写测试:\t\t" << std::fixed << std::setprecision(2) << writeResult << " MB/s" << std::endl;

    // // 释放内存
    // delete[] data;
    /*
    等待重写
    */
    std::cout << "------------------内存测试--------------------" << std::endl;
    std::cout << "内存测试 Test (Fast Mode, 1-Pass @ 5sec)" << std::endl;
    std::cout << "单线程读测试:\t\t" << SB_MEM_OP_READ << " MB/s" << std::endl;
    std::cout << "单线程写测试:\t\t" << SB_MEM_OP_WRITE << " MB/s" << std::endl;

   

} // namespace std;
