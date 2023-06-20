#ifndef MEMBENCH_HPP
#define MEMBENCH_HPP

#include <chrono>
#include <cstring>
#include <iomanip>

// 测试内存读性能并返回结果
double testMemoryReadPerformance(uint64_t* data, int size) {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long sum = 0;
    for (int i = 0; i < size; i += 2) {
        sum += data[i];
        sum += data[i + 1];
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    double transferRateMB = (static_cast<double>(size * sizeof(uint64_t)) / 1048576) / (duration.count() / 1e9);
    return transferRateMB;
}

// 测试内存写性能并返回结果
double testMemoryWritePerformance(uint64_t* data, int size) {
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i += 2) {
        data[i] = i;
        data[i + 1] = i + 1;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    double transferRateMB = (static_cast<double>(size * sizeof(uint64_t)) / 1048576) / (duration.count() / 1e9);
    return transferRateMB;
}

#endif 
