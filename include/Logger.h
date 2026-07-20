#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <iostream>
#include <fstream>
#include "LoggerStream.h"

namespace logger {

    enum class LogLevel 
    {
        DEBUG   = 0,
        INFO    = 1,
        WARNING = 2
    };


    class Logger
    {
        public:
            Logger(std::string, LogLevel);
            ~Logger();

            LoggerStream debug();
            LoggerStream info();
            LoggerStream warning();

        private:
            std::string file_name; 
            LogLevel level; 
            std::ofstream out;

    };
}

#endif