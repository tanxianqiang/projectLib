if (buildNetconf2Server)
# 设定CMake最低版本要求
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

# 设定项目名称
set (mgApp netconf2serverApBeforep)
project(${mgApp})

# 收集源文件
set(SOURCE_FILES
    txqnetconf2server.cpp
)

# 添加可执行文件
add_executable(${mgApp} ${SOURCE_FILES})

# 设置pugixml库路径
set(LIBRARY_DIR /usr/local/lib)
# 设置pugixml头文件路径
set(INCLUDE_DIR /usr/local/include
                /usr/local/include/libnetconf2)
# 将头文件路径添加到包含目录
include_directories(${INCLUDE_DIR})

# 链接pugixml库
target_link_libraries(${mgApp} -L${LIBRARY_DIR} -lnetconf2 -lyang)
set_target_properties(${mgApp} PROPERTIES COMPILE_DEFINITIONS NC_ENABLED_SSH_TLS)
endif()


#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










