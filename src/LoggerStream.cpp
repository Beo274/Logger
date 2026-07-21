#include "../include/LoggerStream.h"
#include "../include/Logger.h"

namespace logger 
{
    LoggerStream::LoggerStream(const std::string& t_level, Logger* t_logger) :  lvl(t_level), logger_(t_logger)
    {
    }

    LoggerStream::~LoggerStream()
    {

        if (!lvl.empty())
        {
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            std::tm* local_tm = std::localtime(&now_time);
            

            std::ostringstream ss;

            ss << std::put_time(local_tm, "%Y-%m-%d %H:%M:%S") << " | " 
               << std::setw(12) << std::right << lvl << " | "
               << buffer.str() << "\n";
            
            logger_->write(ss.str());
        }
    }
    
    std::string LoggerStream::getFormattedLog()
    {
        return formated_msg;
    }
}