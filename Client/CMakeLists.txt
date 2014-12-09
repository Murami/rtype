cmake_minimum_required(VERSION 2.8)
project(R-Type)

include_directories(include/)

SET(CMAKE_CXX_FLAGS "-W -Wall -Wextra -std=c++11")

set(EXECUTABLE_NAME "client")
set(EXECUTABLE_OUTPUT_PATH "../")

add_executable(
	${EXECUTABLE_NAME}
	src/ConfigurationParser.cpp
	src/ConnectionConfiguration.cpp
	src/MenuController.cpp
	src/MenuView.cpp
	src/RtypeClient.cpp
	src/TcpConnection.cpp
	src/main.cpp
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.1 REQUIRED system window graphics network)
find_package(TGUI 0.6 REQUIRED)

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
