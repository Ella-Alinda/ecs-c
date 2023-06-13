#include <cmath>
#include <vector>
#include <thread>

// 多核性能测试函数
double performMultiCoreBenchmark()
{
    const int iterations = 1000000000;  // 运算迭代次数
    double result = 0.0;

    // 使用多个线程进行并行计算
    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(numThreads);

    for (int t = 0; t < numThreads; ++t)
    {
        threads[t] = std::thread([&result, iterations, numThreads, t]() {
            for (int i = t; i < iterations; i += numThreads)
            {
                result += std::sqrt(i);  // 执行浮点数计算
            }
        });
    }

    for (int t = 0; t < numThreads; ++t)
    {
        threads[t].join();
    }

    return result;
}

// 单核性能测试函数
double performSingleCoreBenchmark()
{
    const int iterations = 1000000000;  // 运算迭代次数
    double result = 0.0;

    for (int i = 0; i < iterations; ++i)
    {
        result += std::sqrt(i);  // 执行浮点数计算
    }

    return result;
}
