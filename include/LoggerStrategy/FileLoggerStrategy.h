#ifndef FILELOGGER_H
#define FILELOGGER_H

#pragma once

#include "LoggerStrategy.h"
#include <fstream>


namespace logger 
{
    class FileLoggerStrategy : public LoggerStrategy
    {
    public:
        FileLoggerStrategy(std::string file_name);
        ~FileLoggerStrategy();

        void write(const std::string message) override;

    private:
        std::string file_name;
        std::ofstream out;
    };
}

#endif