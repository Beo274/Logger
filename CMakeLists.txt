cmake_minimum_required(VERSION 3.10.0)
project(Logger VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "src/*.h")


add_library(logger SHARED ${SOURCES} ${HEADERS})


add_executable(Logger ${SOURCES})

include(CTest)
enable_testing()

