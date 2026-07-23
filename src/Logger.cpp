#include "../include/Logger.h"


namespace logger
{
    std::ostream& operator<<(std::ostream& os, LogLevel lvl)
    {
        switch(lvl)
        {
            case LogLevel::DEBUG: return os << "DEBUG";
            case LogLevel::INFO: return os << "INFO";
            case LogLevel::WARNING: return os << "WARNING";
        }
        return os;
    }
    
    Logger& Logger::getInstance()
    {
        static Logger instance;
        return instance;
    }
    
    LogLevel Logger::getLevel()
    {
        return level;
    }
    
    void Logger::init(LoggerStrategy *strategy, LogLevel lvl)
    {
        std::lock_guard<std::mutex> lock(init_mutex);
        this->strategy = strategy;
        this->level = lvl;
    }

    // Logger::Logger(LoggerStrategy* t_strategy, LogLevel t_level) : strategy(t_strategy), level(t_level)
    // {
    // }

    // Logger::Logger(LoggerStrategy* t_strategy) : strategy(t_strategy)
    // {
    // }

    Logger::~Logger()
    {
    }
    
    LoggerStream Logger::debug()
    {
        // Если минимально допустимый уровень меньше, чем уровень сообщения, то все хорошо
        if (level <= LogLevel::DEBUG)
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