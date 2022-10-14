cmake_minimum_required(VERSION 2.81)

project(WayFind)

include_directories(./src/include)
set(SOURCE_EXE sources/main.cpp)
set(SOURCE_LIB sources/myFunctions.cpp)
add_executable(WayFind ${SOURCE_EXE})
add_library(WayFindLib STATIC ${SOURCE_LIB})

target_link_libraries(WayFind WayFindLib)
