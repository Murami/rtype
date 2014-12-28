cmake_minimum_required(VERSION 2.6)
project(monsters C CXX)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/..)
set (LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/..)

set (CTEST_CUSTOM_MAXIMUM_NUMBER_OF_ERRORS 5)

if(WIN32)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -W -Wall -Wextra -std=c++11 -ggdb -g3 -mno-ms-bitfields")
elseif(UNIX)
  SET(CMAKE_CXX_FLAGS "-W -Wall -Wextra -std=c++11 -ggdb -g3 -fmax-errors=5")
endif()

include_directories(include)
include_directories(../include/Game)
include_directories(../include)

#BigMonster
add_library(
  BigMonster SHARED
  src/BigMonster.cpp
  include/BigMonster.hh)

#LittleMonster
add_library(
  LittleMonster SHARED
  src/LittleMonster.cpp
  include/LittleMonster.hh)

