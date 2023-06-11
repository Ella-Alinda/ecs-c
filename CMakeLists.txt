cmake_minimum_required(VERSION 3.12)
project(ECS)

# 添加可执行文件
add_executable(ecs check.cpp)

# 添加头文件搜索路径
include_directories(include) 

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
