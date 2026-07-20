#include "../include/Logger.h"


namespace logger
{
    Logger::Logger(std::string t_file_name, LogLevel t_level) : file_name(t_file_name), level(t_level)
    {
        out.open(file_name, std::ios::out | std::ios::app);
    }

    Logger::Logger(std::string t_file_name) : file_name(t_file_name)
    {
        out.open(file_name, std::ios::out | std::ios::app);
    }

    Logger::~Logger()
    {
        if (out.is_open())
            out.close();
    }
    
    LoggerStream Logger::debug()
    {
        if (level == LogLevel::DEBUG)
        {
            if (!out.is_open())
            {
                out.open(file_name, std::ios::out | std::ios::app);   
            }
            return LoggerStream(out, "DEBUG");
        }
        return LoggerStream(out, "");
    }
    
    LoggerStream Logger::info()
    {
        if (level <= LogLevel::INFO) 
        {
            if (!out.is_open())
            {
                out.open(file_name, std::ios::out | std::ios::app);   
            }
            return LoggerStream(out, "INFO");
        }
        return LoggerStream(out, "");
    }
    
    LoggerStream Logger::warning()
    {
        if (level <= LogLevel::WARNING) 
        {
            if (!out.is_open())
            {
                out.open(file_name, std::ios::out | std::ios::app);   
            }
            return LoggerStream(out, "WARNING");
        }
        return LoggerStream(out, "");
    }
    
    void Logger::setLevel(LogLevel new_lvl)
    {
        this->level = new_lvl;    
    }
}