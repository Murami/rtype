cmake_minimum_required(VERSION 2.6)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/..)
set (CTEST_CUSTOM_MAXIMUM_NUMBER_OF_ERRORS 5)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
include_directories(include/Network)
include_directories(include/Util)
include_directories(include/Application)
add_executable(
server
src/main.cpp
src/Network/Service.cpp
src/Network/TcpSocket.cpp
src/Network/Acceptor.cpp
src/Network/UdpSocket.cpp
src/Network/Timer.cpp
src/Util/Time.cpp
src/Util/Buffer.cpp
src/Application/Server.cpp
src/Application/ClientServer.cpp
include/Network/Acceptor.hh
include/Network/AcceptorObserver.hh
include/Network/NetworkException.hh
include/Network/Service.hh
include/Network/TcpSocket.hh
include/Network/TcpSocketObserver.hh
include/Network/Timer.hh
include/Network/TimerObserver.hh
include/Network/UdpSocket.hh
include/Network/UdpSocketObserver.hh
include/Util/Time.hh
include/Util/Buffer.hh
include/Application/Server.hh
include/Application/ClientServer.hh)
if(WIN32)
  target_link_libraries(server wsock32 ws2_32)
endif()

# add_executable(
# client
# src/Network/Service.cpp
# src/Network/TcpSocket.cpp
# src/Network/Acceptor.cpp
# src/Network/UdpSocket.cpp
# src/Network/Timer.cpp
# src/Util/Time.cpp
# src/Util/Buffer.cpp
# include/Network/Acceptor.hh
# include/Network/AcceptorObserver.hh
# include/Network/NetworkException.hh
# include/Network/Service.hh
# include/Network/TcpSocket.hh
# include/Network/TcpSocketObserver.hh
# include/Network/Timer.hh
# include/Network/TimerObserver.hh
# include/Network/UdpSocket.hh
# include/Network/UdpSocketObserver.hh
# include/Util/Time.hh
# include/Util/Buffer.hh)
# if(WIN32)
#   target_link_libraries(client wsock32 ws2_32)
# endif()