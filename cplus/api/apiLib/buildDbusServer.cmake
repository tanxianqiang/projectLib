
# sudo apt-get install mm-common
# wget https://download.gnome.org/sources/libsigc++/3.0/libsigc%2B%2B-3.0.0.tar.xz
# tar -xvf libsigc++-3.0.0.tar.xz
# cd libsigc++-3.0.0
# ./configure                   --prefix=$PWD/__install
# make && make install

#vim ~/.bashrc        末尾添加   export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
# cmake -DENABLE_EXAMPLES=1 -DENABLE_TOOLS=1  ../
# g++ -o cl txqdbusserver.cpp  `pkg-config --cflags --libs dbus-cxx-2.0`

if (buildDbusServer)
# 设定CMake最低版本要求
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# 设定项目名称
set (mgApp dbusServerApBeforep)
project(${mgApp})

# 查找DBus C++库的编译和链接选项
execute_process(
    COMMAND pkg-config --cflags --libs dbus-cxx-2.0
    OUTPUT_VARIABLE PKG_CONFIG_OUTPUT
    RESULT_VARIABLE PKG_CONFIG_RESULT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(PKG_CONFIG_RESULT)
    message(FATAL_ERROR "Error running pkg-config. Perhaps dbus-cxx-2.0 is not installed?")
endif()

# 将输出分割为编译选项和链接选项
separate_arguments(PKG_CONFIG_OPTIONS UNIX_COMMAND ${PKG_CONFIG_OUTPUT})

# 添加编译选项
add_definitions(${PKG_CONFIG_OPTIONS})

# 收集源文件
set(SOURCE_FILES
    txqdbusserver.cpp
)

# 添加可执行文件
add_executable(${mgApp} ${SOURCE_FILES})
target_link_libraries(${mgApp} ${PKG_CONFIG_OPTIONS})
endif()
