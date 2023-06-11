#include "check.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

std::string getOSVersion() {
    std::string osVersion;
    std::ifstream osReleaseFile("/etc/os-release");
    if (osReleaseFile.is_open()) {
        std::string line;
        while (std::getline(osReleaseFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=')) {
                if (std::getline(iss, value)) {
                    if (key == "PRETTY_NAME") {
                        osVersion = value;
                        break;
                    }
                }
            }
        }
        osReleaseFile.close();
    }
    return osVersion;
}

std::string getProcessorInfo() {
    std::string processorInfo;
    std::ifstream cpuInfoFile("/proc/cpuinfo");
    if (cpuInfoFile.is_open()) {
        std::string line;
        while (std::getline(cpuInfoFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, ':')) {
                if (std::getline(iss, value)) {
                    if (key == "model name") {
                        processorInfo = value;
                        break;
                    }
                }
            }
        }
        cpuInfoFile.close();
    }
    return processorInfo;
}

std::string getProcessorgfrep() {
    std::string processorfrep;
    std::ifstream cpuInfoFile("/proc/cpuinfo");
    if (cpuInfoFile.is_open()) {
        std::string line;
        while (std::getline(cpuInfoFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, ':')) {
                if (std::getline(iss, value)) {
                    if (key == "cpu MHz") {
                        processorfrep = value;
                        break;
                    }
                }
            }
        }
        cpuInfoFile.close();
    }
    return processorfrep;
}

std::string getProcessorgCache() {
    std::string processorCache;
    std::ifstream cpuInfoFile("/proc/cpuinfo");
    if (cpuInfoFile.is_open()) {
        std::string line;
        while (std::getline(cpuInfoFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, ':')) {
                if (std::getline(iss, value)) {
                    if (key == "cache size") {
                        processorCache = value;
                        break;
                    }
                }
            }
        }
        cpuInfoFile.close();
    }
    return processorCache;
}

std::string getAvailableMemory() {
    std::string memoryInfo;
    std::ifstream memInfoFile("/proc/meminfo");
    if (memInfoFile.is_open()) {
        std::string line;
        while (std::getline(memInfoFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, ':')) {
                if (std::getline(iss, value)) {
                    if (key == "MemAvailable") {
                        memoryInfo = value;
                        break;
                    }
                }
            }
        }
        memInfoFile.close();
    }
    return memoryInfo;
}

std::string getDiskSize() {
    std::string command = "df -BG --output=avail / | tail -n 1 | awk '{print $1}'";
    FILE* pipe = popen(command.c_str(), "r");

    char buffer[128];
    std::string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr)
            result += buffer;
    }
    pclose(pipe);

    return std::string(result);
}