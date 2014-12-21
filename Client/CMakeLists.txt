cmake_minimum_required(VERSION 2.8)
project(R-Type)

include_directories(include/ include/Graphic ../new_network_rtype/include/Protocol)

SET(CMAKE_CXX_FLAGS "-W -Wall -Wextra -std=c++11 -ggdb -g3")

set(EXECUTABLE_NAME "client")
set(EXECUTABLE_OUTPUT_PATH "../")

add_executable(
	${EXECUTABLE_NAME}
	src/ConfigurationParser.cpp
	src/Graphic/AObject.cpp
	src/Graphic/BigRocket.cpp
	src/Graphic/LittleRocket.cpp
	src/Graphic/Player.cpp
	src/Graphic/PlayerPowerUp.cpp
	src/Graphic/ScrollingBackground.cpp
	src/Graphic/TextureManager.cpp
	src/Graphic/Monster.cpp
	src/ConnectionConfiguration.cpp
	src/MenuController.cpp
	src/MenuView.cpp
	src/RtypeClient.cpp
	src/TcpConnection.cpp
	src/MyIniParser.cpp
	src/SoundManager.cpp
	src/GameView.cpp
	src/GameController.cpp
	src/ThreadLinux.cpp
	src/ThreadWin32.cpp
	src/NetworkReader.cpp
	src/NetworkWriter.cpp
	src/MutexWin32.cpp
	src/MutexLinux.cpp
	src/Lock.cpp
	src/UdpConnection.cpp
	src/main.cpp
	include/ConfigurationParser.hh
	include/ConnectionConfiguration.hh
	include/GameController.hh
	include/GameEnum.hh
	include/GameObservable.hh
	include/GameView.hh
	include/IGameObserver.hh
	include/IKeyListener.hh
	include/IMenuListener.hh
	include/INetworkListener.hh
	include/IMenuObserver.hh
	include/MenuController.hh
	include/MenuEnum.hh
	include/MenuView.hh
	include/MyIniParser.hh
	include/NetworkReader.hh
	include/MenuObservable.hh
	include/RtypeClient.hh
	include/SoundManager.hh
	include/TcpConnection.hh
	include/Thread.hpp
	include/ThreadLinux.hpp
	include/ThreadWin32.hpp
	include/NetworkWriter.hh
	include/Mutex.hh
	include/MutexLinux.hh
	include/MutexWin32.hh
	include/Lock.hh
	include/UdpConnection.hh
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.1 REQUIRED system window graphics network audio)
find_package(TGUI 0.6 REQUIRED)

if (UNIX)
	target_link_libraries(client pthread)
elseif(WIN32)
  target_link_libraries(client wsock32 ws2_32)
endif()

if(SFML_FOUND)
	include_directories(
		${SFML_INCLUDE_DIR}
)
	target_link_libraries(
		${EXECUTABLE_NAME}
		${SFML_LIBRARIES}
)
endif()

if(TGUI_FOUND)
	include_directories(
		${TGUI_INCLUDE_DIR}
)
	target_link_libraries(
		${EXECUTABLE_NAME}
		${TGUI_LIBRARY}
)
endif()
