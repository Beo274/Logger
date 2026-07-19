#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <iostream>
#include <fstream>
#include "../include/MessageFormat.h"

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

        void debug(std::string);
        void info(std::string);
        void warning(std::string);

        friend std::ostream& operator<< (std::ostream& os, const Logger& logger);

    private:
        std::string file_name; 
        LogLevel level; 
        std::ofstream out;

    };
}

#endif