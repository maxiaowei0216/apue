set(SRC_LIST "4.7.c")


# 添加 ch4 子目录
#add_subdirectory(${PROJECT_SOURCE_DIR}/apue)

add_executable(ch4 ${SRC_LIST})

# 添加链接库
target_link_libraries(ch4 ErrFunc)