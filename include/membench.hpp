#ifndef MEMBENCH_HPP
#define MEMBENCH_HPP

#include <chrono>
#include <cstring>
#include <iomanip>

// 测试内存读性能并返回结果
double testMemoryReadPerformance(__uint128_t* data, int size) {
    auto startTime = std::chrono::high_resolution_clock::now();
    volatile __uint128_t sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; i += 4) {
        __uint128_t val1 = data[i];
        __uint128_t val2 = data[i + 1];
        __uint128_t val3 = data[i + 2];
        __uint128_t val4 = data[i + 3];
        sum += val1 + val2 + val3 + val4;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    double transferRateMB = (static_cast<double>(size * sizeof(__uint128_t)) / 1048576) / (duration.count() / 1e9);
    return transferRateMB;
}

// 测试内存写性能并返回结果
double testMemoryWritePerformance(__uint128_t* data, int size) {
    auto startTime = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < size; i += 4) {
        data[i] = i;
        data[i + 1] = i + 1;
        data[i + 2] = i + 2;
        data[i + 3] = i + 3;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    double transferRateMB = (static_cast<double>(size * sizeof(__uint128_t)) / 1048576) / (duration.count() / 1e9);
    return transferRateMB;
}



#endif 
