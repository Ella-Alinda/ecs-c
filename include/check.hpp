#ifndef CHECK_HPP
#define CHECK_HPP

#include <string>

// 获取操作系统版本信息
std::string getOSVersion();

// 获取CPU信息
std::string getProcessorInfo();

// 获取可用MEM信息
std::string getAvailableMemory();

//获取CPU频率
std::string getProcessorgfrep();

//获取CPU缓存
std::string getProcessorgCache();

//获取硬盘大小
std::string getDiskSize();

#endif  // CHECK_HPP
