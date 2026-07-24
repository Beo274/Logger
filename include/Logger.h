#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include "LoggerStream.h"
#include "LoggerStrategy/LoggerStrategy.h"



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
            static Logger& getInstance();
            static LogLevel getLevel();
            void init(LoggerStrategy *strategy, LogLevel lvl = LogLevel::INFO);

            Logger(Logger &other) = delete;
            void operator=(const Logger&) = delete;
            
            ~Logger();

            LoggerStream debug();
            LoggerStream info();
            LoggerStream warning();

            void setLevel(LogLevel);

            void setStrategy(LoggerStrategy&);

            void write(std::string);

        private:
            Logger() = default;

            std::mutex init_mutex;

            LoggerStrategy* strategy;
            std::string file_name; 
            static inline LogLevel level = LogLevel::INFO; 
            std::ofstream out;

    };


#endif