set(SRC_LIST "9.2.c")


# 添加子目录
#add_subdirectory(${PROJECT_SOURCE_DIR}/apue)

add_executable(exc ${SRC_LIST})

# 添加链接库
target_link_libraries(exc apueLib)