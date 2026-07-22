#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <iostream>
#include <fstream>
#include "LoggerStream.h"
#include "LoggerStrategy/LoggerStrategy.h"

namespace logger {

    enum class LogLevel 
    {
        DEBUG   = 1,
        INFO    = 2,
        WARNING = 3,
        NO      = 4  // Если уровень логирования введен неверно
    };

    std::ostream& operator<<(std::ostream& os, LogLevel lvl);

    class Logger
    {
        public:
            Logger(LoggerStrategy *strategy, LogLevel lvl);
            Logger(LoggerStrategy *strategy);
            Logger();
            ~Logger();

            LoggerStream debug();
            LoggerStream info();
            LoggerStream warning();

            void setLevel(LogLevel);

            void setStrategy(LoggerStrategy&);

            void write(std::string);

        private:
            LoggerStrategy* strategy;
            std::string file_name; 
            LogLevel level = LogLevel::INFO; 
            std::ofstream out;

    };
}

#endif