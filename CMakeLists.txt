# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (APUE)

# 添加头文件路径
include_directories("${PROJECT_SOURCE_DIR}/apue/include")

# 设定可执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
# 添加子目录
add_subdirectory(apue)
add_subdirectory(ch4)
add_subdirectory(ch6)
add_subdirectory(ch8)
add_subdirectory(ch9)
