cmake_minimum_required(VERSION 2.6)
project(rtype C CXX)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/..)
set (CTEST_CUSTOM_MAXIMUM_NUMBER_OF_ERRORS 5)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
include_directories(include)
# todo refaire tous les includes ...
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
src/Game/CollisionEvent.cpp
src/Game/CoreEventDestroy.cpp
src/Game/DestroyableSet.cpp
src/Game/EntityEventMove.cpp
src/Game/Player.cpp
src/Game/CollisionReceiver.cpp
src/Game/CoreEventReceiver.cpp
src/Game/Entity.cpp
src/Game/EntityEventReceiver.cpp
src/Game/Projectile.cpp
src/Game/Core.cpp
src/Game/CoreEventSpawn.cpp
src/Game/EntityEventLife.cpp
src/Game/Monster.cpp
src/Physic/Body.cpp
src/Physic/BodyEventCollide.cpp
src/Physic/BodyEventMove.cpp
src/Physic/BodyEventReceiver.cpp
src/Physic/World.cpp
src/Util/Time.cpp
src/Util/Buffer.cpp
src/Util/Lock.cpp
src/Util/MutexLinux.cpp
src/Util/ThreadWin32.cpp
src/Util/Vec2.cpp
src/Util/IDGenerator.cpp
src/Util/MutexWin32.cpp
src/Util/ThreadLinux.cpp
src/Util/Time.cpp
src/Application/Server.cpp
src/Application/ClientServer.cpp
include/Game/CollisionEvent.hh
include/Game/CoreEvent.hh
include/Game/DestroyableSet.hh
include/Game/EntityEventReceiver.hh
include/Game/Projectile.hh
include/Game/CollisionReceiver.hh
include/Game/CoreEventReceiver.hh
include/Game/EntityEvent.hh
include/Game/Entity.hh
include/Game/CollisionSystem.hh
include/Game/CoreEventSpawn.hh
include/Game/EntityEventLife.hh
include/Game/Monster.hh
include/Game/CoreEventDestroy.hh
include/Game/Core.hh
include/Game/EntityEventMove.hh
include/Game/Player.hh
include/Physic/BodyContainer.hh
include/Physic/BodyEvent.hh
include/Physic/BodyEventReceiver.hh
include/Physic/Shape.hh
include/Physic/World.hh
include/Physic/BodyEventCollide.hh
include/Physic/BodyEventMove.hh
include/Physic/Body.hh
include/Physic/WorldEvent.hh
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
include/Util/Lock.hh
include/Util/Mutex.hh
include/Util/MutexWin32.hh
include/Util/Observable.tpp
include/Util/Receiver.hpp
include/Util/ThreadLinux.hpp
include/Util/Time.hh
include/Util/IDGenerator.hh
include/Util/Msg.hpp
include/Util/MutexLinux.hh
include/Util/Observable.hpp
include/Util/Observer.hpp
include/Util/Thread.hpp
include/Util/ThreadWin32.hpp
include/Util/Vec2.hh
include/Application/ClientRoom.hh
include/Application/Room.hh
include/Application/Server.hh
include/Application/ClientServer.hh)
if(WIN32)
  target_link_libraries(server wsock32 ws2_32)
elseif(UNIX)
  target_link_libraries(server pthread)
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