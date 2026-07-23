add_library(LoggerLib
    Logger.cpp
    LoggerStream.cpp
    LoggerStrategy/LoggerStrategy.cpp
    LoggerStrategy/FileLoggerStrategy.cpp
    LoggerStrategy/SocketLoggerStrategy.cpp
)

set_target_properties(LoggerLib PROPERTIES
    OUTPUT_NAME "logger"
)

target_include_directories(LoggerLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(LoggerLib PRIVATE LOGGER_EXPORTS)
else()
    target_compile_definitions(LoggerLib PUBLIC LOGGER_STATIC)
endif()