#include <iostream>
#include <chrono>
#include <cstdlib>  // 用于随机数生成
#include <ctime>    // 用于随机数种子
#include <cstdint>  // 用于固定大小整数类型
#include <cstring>  // 用于内存操作
#include "membench.hpp"

const int arraySize = 1000000; // 要测试的数组大小，可以根据需要调整
const int maxOffset = 255;     // 内存块的最大偏移量，根据sysbench代码中的max_offset调整

void event_rnd_write(int* buffer) {
    for (int i = 0; i <= maxOffset; i++) {
        int offset = rand() % maxOffset;
        buffer[offset] = i;
    }
}

void event_rnd_read(int* buffer) {
    for (int i = 0; i <= maxOffset; i++) {
        int offset = rand() % maxOffset;
        int val = buffer[offset];
        // 防止编译器优化未使用的变量
        volatile int unused = val;
    }
}

int main() {
    // 创建一个数组
    int* arr = new int[arraySize];
    
    // 设置随机数种子
    std::srand(std::time(nullptr));

    // 顺序写入数据
    auto startWrite = std::chrono::high_resolution_clock::now();
    event_rnd_write(arr);
    auto endWrite = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> writeTime = endWrite - startWrite;
    std::cout << "随机写入时间: " << writeTime.count() << " 秒" << std::endl;

    // 顺序读取数据
    auto startRead = std::chrono::high_resolution_clock::now();
    event_rnd_read(arr);
    auto endRead = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> readTime = endRead - startRead;
    std::cout << "随机读取时间: " << readTime.count() << " 秒" << std::endl;

    // 输出读写速度
    double writeSpeed = static_cast<double>(maxOffset * sizeof(int)) / (writeTime.count() * 1024 * 1024);
    double readSpeed = static_cast<double>(maxOffset * sizeof(int)) / (readTime.count() * 1024 * 1024);

    std::cout << "随机写入速度: " << writeSpeed << " MB/s" << std::endl;
    std::cout << "随机读取速度: " << readSpeed << " MB/s" << std::endl;

    // 释放内存
    delete[] arr;

    return 0;
}
