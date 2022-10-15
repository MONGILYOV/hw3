cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(WayFind)

add_library(${PROJECT_NAME} STATIC
        sources/myFunctions.cpp
        )

add_executable(WayFindExecutable
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )

target_link_libraries(WayFindExecutable ${PROJECT_NAME})