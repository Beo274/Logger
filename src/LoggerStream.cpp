#include "../include/LoggerStream.h"
#include "../include/Logger.h"


    LoggerStream::LoggerStream(const std::string& t_level, Logger* t_logger) :  lvl(t_level), logger_(t_logger)
    {
    }

    LoggerStream::~LoggerStream()
    {

        if (!lvl.empty())
        {
            // Создание текущего времени и перевод в tm формат
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            std::tm local_tm{};
            ::localtime_r(&now_time, &local_tm);

            char time_buf[32];
            std::strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", &local_tm);
            

            std::ostringstream ss;
            ss.imbue(std::locale::classic());

            // Запись в текстовый поток
            ss << time_buf << " | " 
               << std::setw(7) << std::right << lvl << " | "
               << buffer.str() << "\n";
            
            // Возвращение в основной класс логгера итоговую строку
            logger_->write(ss.str());
        }
    }
