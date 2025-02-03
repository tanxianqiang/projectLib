if (buildLib)

set (mgLib tanxianqiang)

# 设定项目名称
project(${mgLib})

# 查找源文件
file(GLOB SOURCE_FILES_LAB txqarg.cpp
                           txqlocalclient.cpp
                           txqlocalserver.cpp
                           txqstring.cpp
                           txqlog.cpp
                           txqxml.cpp
                           txqexcel.cpp
                           txqdbusclient.cpp
                           txqdbusserver.cpp
                           txqtestenv.cpp
                           txqtesttest.cpp
                           txqnetconf2server.cpp
                           txqnetconf2client.cpp)

# 设置pugixml库路径
set(LIBRARY_DIR /usr/local/lib)

# 设置pugixml头文件路径
set(INCLUDE_DIR /usr/local/include
                /usr/local/include/libnetconf2)
include_directories(${INCLUDE_DIR})

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


# 生成静态库
add_library(${mgLib} STATIC ${SOURCE_FILES_LAB})
set_target_properties(${mgLib} PROPERTIES COMPILE_FLAGS "-g")

# 链接库
target_link_libraries(${mgLib} -L${LIBRARY_DIR}  ${PKG_CONFIG_OPTIONS}
                      -ldbus-cxx -lxlnt -lspdlog -lpugixml -lnetconf2 -lyang)
set_target_properties(${mgLib} PROPERTIES COMPILE_DEFINITIONS NC_ENABLED_SSH_TLS)
# 安装库文件
install(TARGETS ${mgLib}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

file(GLOB SOURCE_HEADERS *.h)

# 安装头文件
install(FILES ${SOURCE_HEADERS} DESTINATION include)
endif()

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////