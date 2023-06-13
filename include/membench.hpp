#ifndef MEMBENCH_HPP
#define MEMBENCH_HPP

#include <chrono>
#include <cstring>
#include <iomanip>

// 测试内存读性能并返回结果
double testMemoryReadPerformance(int* data, int size) {
    auto startTime = std::chrono::high_resolution_clock::now();
    volatile long long sum = 0; // 使用 volatile 避免编译器优化
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    double dataRate = static_cast<double>(size * sizeof(int)) / (1024 * 1024) / (duration.count() / 1000.0);
    return dataRate;
}

// 测试内存写性能并返回结果
double testMemoryWritePerformance(int* data, int size) {
    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; ++i) {
        data[i] = i;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    double dataRate = static_cast<double>(size * sizeof(int)) / (1024 * 1024) / (duration.count() / 1000.0);
    return dataRate;
}

#endif 