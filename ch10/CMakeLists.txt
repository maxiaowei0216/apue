# 加入本文件下的所有源文件
file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/ *.c )

# 分别编译为可执行文件
foreach( sourcefile IN LISTS APP_SOURCES )
    string( REPLACE ".c" "" program ${sourcefile} )
    add_executable( ${program} ${sourcefile} )
    target_link_libraries( ${program} apueLib )
endforeach( sourcefile )