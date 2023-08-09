#include <iostream>
#include <chrono>

int main() {

  const int arraySize = 1024 * 1024 * 100; // 100MB
  char* array = new char[arraySize];

  // 写速度测试
  auto writeStart = std::chrono::high_resolution_clock::now(); 
  for (int i = 0; i < arraySize; i++) {
    array[i] = 0; 
  }
  auto writeEnd = std::chrono::high_resolution_clock::now();

  // 读速度测试
  auto readStart = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < arraySize; i++) {
    char value = array[i];
  } 
  auto readEnd = std::chrono::high_resolution_clock::now();

  // 计算时间
  auto writeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(writeEnd - writeStart).count();
  auto readDuration = std::chrono::duration_cast<std::chrono::milliseconds>(readEnd - readStart).count();

  // 输出结果
  double writeSpeed = arraySize / (writeDuration * 1000.0);
  std::cout << "Write speed: " << writeSpeed << " MB/s" << std::endl;
  
  double readSpeed = arraySize / (readDuration * 1000.0);
  std::cout << "Read speed: " << readSpeed << " MB/s" << std::endl;

  delete[] array;

  return 0;
}