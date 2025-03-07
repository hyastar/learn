# CMakeLists.txt for tinytetris project
cmake_minimum_required(VERSION 3.0)
project(tinytetris)

# 设置 C++ 标准为 C++11
set(CMAKE_CXX_STANDARD 11)

# 添加源文件
add_executable(tinytetris tinytetris.cpp)

