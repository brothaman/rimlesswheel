cmake_minimum_required( VERSION 3.1)

project( rimless_robot)

set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")
set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -std=c89")
set (UTILITIES_DIR "${CMAKE_SOURCE_DIR}/src/utility")
add_subdirectory(src)
