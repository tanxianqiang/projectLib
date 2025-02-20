
# 设定CMake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设定C++标准
include(buildLib.cmake)

# nc -U /tmp/mysocket.sock 连接服务端
include(buildLocalClient.cmake)
include(buildLocalServer.cmake)
include(buildString.cmake)
include(buildArg.cmake)
include(buildXml.cmake)
include(buildTest.cmake)
include(buildLog.cmake)
include(buildExcel.cmake)
include(buildDbusClient.cmake)
include(buildDbusServer.cmake)
include(buildNetconf2Client.cmake)
include(buildNetconf2Server.cmake)
include(buildIpcs.cmake)
include(buildApiLibDoc.cmake)




