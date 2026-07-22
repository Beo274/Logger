#include "../include/Logger.h"


namespace logger
{
    Logger::Logger(std::string t_file_name, LogLevel t_level) : file_name(t_file_name), level(t_level)
    {
    }

    Logger::Logger(std::string t_file_name) : file_name(t_file_name)
    {
    }

    Logger::~Logger()
    {
    }
    
    LoggerStream Logger::debug()
    {
        if (level == LogLevel::DEBUG)
        {
            // Возвращает поток, который сохраняет в себя всё и форматирует итоговую строку
            return LoggerStream("DEBUG", this);
        }
        return LoggerStream("", this);
    }
    
    LoggerStream Logger::info()
    {
        if (level <= LogLevel::INFO) 
        {
            return LoggerStream("INFO", this);
        }
        return LoggerStream("", this);
    }
    
    LoggerStream Logger::warning()
    {
        if (level <= LogLevel::WARNING) 
        {
            return LoggerStream("WARNING", this);
        }
        return LoggerStream("", this);
    }
    
    void Logger::setLevel(LogLevel new_lvl)
    {
        this->level = new_lvl;    
    }
    
    void Logger::setStrategy(LoggerStrategy& strategy)
    {
        this->strategy = &strategy;
    }
    
    void Logger::write(std::string msg)
    {
        strategy->write(msg);
    }
}