cmake_minimum_required(VERSION 3.5)

project(lab_09 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(benchmark REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ./src)

include_directories(${SOURCE_DIR})

add_definitions(-Wall -Wextra -m80387 -mno-sse -O0)

set(PROJECT_SOURCES
    ${SOURCE_DIR}/benchmark.cpp
)

set_property(SOURCE ${PROJECT_SOURCES} PROPERTY CXX_STANDARD 11)

add_executable(lab_09.out ${PROJECT_SOURCES})

target_link_libraries(lab_09.out benchmark::benchmark)
