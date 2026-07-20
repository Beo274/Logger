#ifndef LOGGERSTREAM_H
#define LOGGERSTREAM_H

#pragma once

#include <sstream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <iostream>

namespace logger {

    class LoggerStream {
    public:
        LoggerStream(std::ofstream&, const std::string&);
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
        std::ofstream& out;
        std::string lvl;
        std::ostringstream buffer;
    };

}

#endif