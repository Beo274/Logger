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
    
    void Logger::debug(std::string msg)
    {
        if (level >= LogLevel::DEBUG)
        {
            MessageFormat message_format(msg, "DEBUG");
            out.open(file_name, std::ios::out | std::ios::app);
            if (out.is_open())
            {
                out << message_format.format_message();
            }
            else 
            {
                std::cerr << "Не удалось открыть файл логов" << std::endl;
            }
            out.close();
        }
    }
    
    void Logger::info(std::string msg)
    {
        if (level >= LogLevel::INFO) 
        {
            MessageFormat message_format(msg, "INFO");
            out.open(file_name, std::ios::out | std::ios::app);
            if (out.is_open())
            {
                out << message_format.format_message();
                out.close();
            }
            else 
            {
                std::cerr << "Не удалось открыть файл логов" << std::endl;
            }
        }
    }
    
    void Logger::warning(std::string msg)
    {
        if (level == LogLevel::WARNING) 
        {
            MessageFormat message_format(msg, "WARNING");
            out.open(file_name, std::ios::out | std::ios::app);
            if (out.is_open())
            {
                out << message_format.format_message();
                out.close();
            }
            else 
            {
                std::cerr << "Не удалось открыть файл логов" << std::endl;
            }
        }
    }
}