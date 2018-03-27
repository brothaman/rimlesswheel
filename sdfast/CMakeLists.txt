cmake_minimum_required( VERSION 3.1)

project( rimless_robot)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")
set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -std=c89")
add_subdirectory(src)
