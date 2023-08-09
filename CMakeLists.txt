cmake_minimum_required(VERSION 3.12)
project(ECS)

set(CMAKE_CXX_FLAGS_RELWITHDEBUGINFO "-O3 -g")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 添加头文件目录
include_directories(include)

# 添加源文件
set(SOURCES
    src/check.cpp
    src/main.cpp
    src/sb_memory.c
)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})
