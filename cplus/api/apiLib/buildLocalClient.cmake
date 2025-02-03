if (buildLocalClient)
# 设定CMake最低版本要求
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

# 设定项目名称
set (mgApp localClientApp)
project(${mgApp})

# 收集源文件
set(SOURCE_FILES
    txqlocalclient.cpp
)

# 添加可执行文件
add_executable(${mgApp} ${SOURCE_FILES})
set_target_properties(${mgApp} PROPERTIES COMPILE_FLAGS "-g")
#set_target_properties(${mgApp} PROPERTIES LINK_FLAGS "-s")
endif()

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////