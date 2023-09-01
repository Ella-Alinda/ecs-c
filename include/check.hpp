#ifndef CHECK_HPP
#define CHECK_HPP

#include <string>
#include <cmath>
extern "C"

std::string getCPUModel();
int getCPUCores();
double getCPUFrequency();
int getCPUCacheL1();
int getCPUCacheL2();
int getCPUCacheL3();
unsigned long long getDiskTotalSpace(const std::string& path);
unsigned long long getDiskUsedSpace(const std::string& path);
unsigned long long getMemoryTotal();
unsigned long long getMemoryUsed();
unsigned long long getSwapTotal();
unsigned long long getSwapUsed();
std::string getSystemVersion();
std::string formatSize(unsigned long long sizeInBytes);
void generateSystemInfoHeader();

#endif  // CHECK_HPP
