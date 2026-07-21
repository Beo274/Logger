#include "../../include/LoggerStrategy/FileLoggerStrategy.h"

namespace logger 
{
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

    void FileLoggerStrategy::write(std::string message) 
    {
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
}