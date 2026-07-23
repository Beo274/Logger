#include "../../include/LoggerStrategy/FileLoggerStrategy.h"


    FileLoggerStrategy::FileLoggerStrategy(std::string t_file_name) : file_name(t_file_name)
    {
        if (!out.is_open())
            out.open(file_name, std::ios::out | std::ios::app);
    }

    FileLoggerStrategy::~FileLoggerStrategy()
    {
        if (out.is_open())
            out.close();
    }

    void FileLoggerStrategy::write(const std::string& message) 
    {
        std::lock_guard<std::mutex> lock(locker);
        if (out.is_open())
        {
            out << message;
            out.flush();
        }
        else
        {
            out.open(file_name, std::ios::out | std::ios::app);
            out << message;
            out.flush();
        }
    }
