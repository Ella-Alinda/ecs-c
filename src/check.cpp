#include "check.hpp"
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <cmath>
#include <string>
extern "C"

std::string formatSize(unsigned long long sizeInBytes) {
    const unsigned int base = 1024;
    const char* units[] = {"B", "KB", "MB", "GB"};

    int unitIndex = 0;
    double size = static_cast<double>(sizeInBytes);

    while (size >= base && unitIndex < 3) {
        size /= base;
        unitIndex++;
    }

    char formattedSize[16];
    std::snprintf(formattedSize, sizeof(formattedSize), "%.2f %s", size, units[unitIndex]);
    return std::string(formattedSize);
}


std::string getCPUModel() {
    std::string cpuModel;
    std::ifstream cpuInfo("/proc/cpuinfo");
    if (cpuInfo.is_open()) {
        std::string line;
        while (std::getline(cpuInfo, line)) {
            if (line.find("model name") != std::string::npos) {
                size_t pos = line.find(":");
                if (pos != std::string::npos) {
                    cpuModel = line.substr(pos + 2);
                    cpuModel.erase(cpuModel.find_last_not_of(" \n\r\t") + 1);
                    break;
                }
            }
        }
        cpuInfo.close();
    }
    return cpuModel;
}

int getCPUCores() {
    return std::thread::hardware_concurrency();
}

double getCPUFrequency() {
    std::string frequencyStr;
    std::ifstream cpuInfo("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq");
    if (cpuInfo.is_open()) {
        std::getline(cpuInfo, frequencyStr);
        cpuInfo.close();
    }
    if (!frequencyStr.empty()) {
        return std::stod(frequencyStr) / 1000.0;
    }
    return 0.0;
}

int getCPUCache() {
    return 30720;
}

unsigned long long getDiskTotalSpace(const std::string& path) {
    struct statvfs diskInfo;
    if (statvfs(path.c_str(), &diskInfo) != -1) {
        return diskInfo.f_frsize * diskInfo.f_blocks;
    }
    return 0;
}

unsigned long long getDiskUsedSpace(const std::string& path) {
    struct statvfs diskInfo;
    if (statvfs(path.c_str(), &diskInfo) != -1) {
        return diskInfo.f_frsize * (diskInfo.f_blocks - diskInfo.f_bfree);
    }
    return 0;
}

unsigned long long getMemoryTotal() {
    struct sysinfo memInfo;
    if (sysinfo(&memInfo) != -1) {
        return memInfo.totalram * memInfo.mem_unit;
    }
    return 0;
}

unsigned long long getMemoryUsed() {
    struct sysinfo memInfo;
    if (sysinfo(&memInfo) != -1) {
        return (memInfo.totalram - memInfo.freeram) * memInfo.mem_unit;
    }
    return 0;
}

unsigned long long getSwapTotal() {
    struct sysinfo memInfo;
    if (sysinfo(&memInfo) != -1) {
        return memInfo.totalswap * memInfo.mem_unit;
    }
    return 0;
}

unsigned long long getSwapUsed() {
    struct sysinfo memInfo;
    if (sysinfo(&memInfo) != -1) {
        return (memInfo.totalswap - memInfo.freeswap) * memInfo.mem_unit;
    }
    return 0;
}

std::string getSystemVersion() {
    struct utsname sysInfo;
    if (uname(&sysInfo) != -1) {
        return sysInfo.release;
    }
    return "";
}

void generateSystemInfoHeader() {
    std::string cpuModel = getCPUModel();
    int cpuCores = getCPUCores();
    double cpuFrequency = getCPUFrequency();
    int cpuCache = getCPUCache();
    unsigned long long diskTotal = getDiskTotalSpace("/");
    unsigned long long diskUsed = getDiskUsedSpace("/");
    unsigned long long memoryTotal = getMemoryTotal();
    unsigned long long memoryUsed = getMemoryUsed();
    unsigned long long swapTotal = getSwapTotal();
    unsigned long long swapUsed = getSwapUsed();
    std::string formattedDiskTotal = formatSize(diskTotal);
    std::string formattedDiskUsed = formatSize(diskUsed);
    std::string formattedMemoryTotal = formatSize(memoryTotal);
    std::string formattedMemoryUsed = formatSize(memoryUsed);
    std::string formattedSwapTotal = formatSize(swapTotal);
    std::string formattedSwapUsed = formatSize(swapUsed);
    std::string systemVersion = getSystemVersion();

    std::cout << "#ifndef CHECK_HPP" << std::endl;
    std::cout << "#define CHECK_HPP" << std::endl;
    std::cout << std::endl;
    std::cout << "const char* const CPU_MODEL = \"" << cpuModel << "\";" << std::endl;
    std::cout << "const int CPU_CORES = " << cpuCores << ";" << std::endl;
    std::cout << "const double CPU_FREQUENCY = " << cpuFrequency << ";" << std::endl;
    std::cout << "const int CPU_CACHE = " << cpuCache << ";" << std::endl;
    std::cout << "const unsigned long long DISK_TOTAL = " << diskTotal << "ULL;" << std::endl;
    std::cout << "const unsigned long long DISK_USED = " << diskUsed << "ULL;" << std::endl;
    std::cout << "const unsigned long long MEMORY_TOTAL = " << memoryTotal << "ULL;" << std::endl;
    std::cout << "const unsigned long long MEMORY_USED = " << memoryUsed << "ULL;" << std::endl;
    std::cout << "const unsigned long long SWAP_TOTAL = " << swapTotal << "ULL;" << std::endl;
    std::cout << "const unsigned long long SWAP_USED = " << swapUsed << "ULL;" << std::endl;
    std::cout << "const std::string DISK_TOTAL = \"" << formattedDiskTotal << "\";" << std::endl;
    std::cout << "const std::string DISK_USED = \"" << formattedDiskUsed << "\";" << std::endl;
    std::cout << "const std::string MEMORY_TOTAL = \"" << formattedMemoryTotal << "\";" << std::endl;
    std::cout << "const std::string MEMORY_USED = \"" << formattedMemoryUsed << "\";" << std::endl;
    std::cout << "const std::string SWAP_TOTAL = \"" << formattedSwapTotal << "\";" << std::endl;
    std::cout << "const std::string SWAP_USED = \"" << formattedSwapUsed << "\";" << std::endl;
    
    std::cout << "const char* const SYSTEM_VERSION = \"" << systemVersion << "\";" << std::endl;
    std::cout << std::endl;
    std::cout << "#endif" << std::endl;
}
