if (buildLocalServer)
# 设定CMake最低版本要求
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

# 设定项目名称
set (mgApp localServerApBeforep)
project(${mgApp})

# 收集源文件
set(SOURCE_FILES
    txqlocalserver.cpp
)

# 添加可执行文件
add_executable(${mgApp} ${SOURCE_FILES})
endif()

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////