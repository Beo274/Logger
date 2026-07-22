#include <iostream>
#include <cstdlib>
#include "../include/Logger.h"
#include "../include/LoggerStrategy/LoggerStrategy.h"
#include "../include/LoggerStrategy/FileLoggerStrategy.h"
#include "../include/LoggerStrategy/SocketLoggerStrategy.h"

logger::LogLevel toLogLevel(std::string str_lvl)
{
    if (str_lvl == "DEBUG")    return logger::LogLevel::DEBUG;  
    if (str_lvl == "WARNING")  return logger::LogLevel::WARNING;
    // По умолчанию 
    return logger::LogLevel::INFO;
}

int main(int argc, char* argv[])
{
    std::string file_name = argv[1];
    logger::LogLevel log_lvl = toLogLevel(argv[2]);
    // 0 - file, 1 - socket
    int strategy_number = 0;
    std::cout << "Введите способ логирования: ";
    std::cin >> strategy_number;
    logger::LoggerStrategy *strategy;
    if (strategy_number == 0) 
    {
        strategy = new logger::FileLoggerStrategy(argv[1]);
    }
    else
    {
        strategy = new logger::SocketLoggerStrategy("127.0.0.1", 9000);
    }
    logger::Logger log(strategy, logger::LogLevel::INFO);
    int lvl = 0;
    std::cout << "Введите численный уровень лога: ";
    std::cin >> lvl;
    std::cin.ignore();

    std::string msg;
    std::cout << "Введите сообщение лога: ";
    std::getline(std::cin, msg);
    switch (lvl)
    {
    case 0:
    {
        log.debug() << "Полученное сообщение: " << msg;
        break;
    }
    case 1:
    {
        log.info() << "Полученное сообщение: " << msg;
        break;
    }
    case 2:
    {
        log.warning() << "Полученное сообщение: " << msg;
        break;
    }
    }
}
