#include "../include/Logger.h"


namespace logger
{
    Logger::Logger(std::string t_file_name, LogLevel t_level) : file_name(t_file_name), level(t_level)
    {
    }

    Logger::~Logger()
    {
        if (out.is_open())
            out.close();
    }
    
    LoggerStream Logger::debug()
    {
        if (level >= LogLevel::DEBUG)
        {
            out.open(file_name, std::ios::out | std::ios::app);
            if (out.is_open())
            {
                return LoggerStream(out, "DEBUG");
            }
            else
                std::cerr << "Не удалось открыть файл логов" << std::endl;
        }
        return LoggerStream(out, "");
    }
    
    LoggerStream Logger::info()
    {
        if (level >= LogLevel::INFO) 
        {
            out.open(file_name, std::ios::out | std::ios::app);
            if (out.is_open())
            {
                return LoggerStream(out, "INFO");
            }
            else
                std::cerr << "Не удалось открыть файл логов" << std::endl;
            
        }
        return LoggerStream(out, "");
    }
    
    LoggerStream Logger::warning()
    {
        if (level == LogLevel::WARNING) 
        {
            out.open(file_name, std::ios::out | std::ios::app);
            if (out.is_open())
            {
                return LoggerStream(out, "WARNING");
            }
            else
                std::cerr << "Не удалось открыть файл логов" << std::endl;
        }
        return LoggerStream(out, "");
    }
}