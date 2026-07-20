cmake_minimum_required(VERSION 3.10.0)
project(Logger VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "src/*.h")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_library(logger ${SOURCES} ${HEADERS})

target_include_directories(logger PUBLIC include)

add_executable(Logger src/main.cpp)
target_link_libraries(Logger PRIVATE logger)

include(CTest)
enable_testing()

