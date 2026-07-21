#ifndef LOGGERSTREAM_H
#define LOGGERSTREAM_H

#pragma once

#include <sstream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <iostream>

namespace logger {

    class Logger;

    class LoggerStream {
    public:
        LoggerStream(const std::string&, Logger*);
        ~LoggerStream();

        template <typename T>
        LoggerStream& operator<<(const T& value) {
            if (!lvl.empty())
            {
                buffer << value;
            }
            return *this; 
        }

    private:
        Logger *logger_;
        std::string lvl;
        std::ostringstream buffer;
    };
}

#endif