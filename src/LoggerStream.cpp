#include "../include/LoggerStream.h"


namespace logger {

    LoggerStream::LoggerStream(std::ofstream& t_out, const std::string& t_level) : out(t_out), lvl(t_level)
    {
    }

    LoggerStream::~LoggerStream()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* local_tm = std::localtime(&now_time);
        
        out << std::put_time(local_tm, "%Y-%m-%d %H:%M:%S") << "  | "
            << std::setw(12) << std::right << lvl << " | "
            << buffer.str() << "\n";
    }
}