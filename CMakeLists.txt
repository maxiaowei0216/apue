# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (APUE)

# 添加头文件路径
include_directories("${PROJECT_SOURCE_DIR}/apue/include")
add_subdirectory(apue)
add_subdirectory(ch9 bin)
