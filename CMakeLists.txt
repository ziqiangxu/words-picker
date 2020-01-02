
set(TARGET_NAME words-picker)      # 设置目标名字
project (TARGET_NAME)
cmake_minimum_required(VERSION 2.8)

# 指定构建类型
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_BUILD_TYPE Release)

add_subdirectory(src)