#include <iostream>
#include <cstdlib>
#include "../include/Logger.h"
#include "../include/LoggerStrategy/LoggerStrategy.h"
#include "../include/LoggerStrategy/FileLoggerStrategy.h"
#include "../include/LoggerStrategy/SocketLoggerStrategy.h"

logger::LogLevel toLogLevel(std::string str_lvl)
{
    if (str_lvl == "DEBUG")    return logger::LogLevel::DEBUG;  
    if (str_lvl == "INFO")    return logger::LogLevel::INFO; 
    if (str_lvl == "WARNING")  return logger::LogLevel::WARNING;
    // По умолчанию 
    return logger::LogLevel::NO;
}


int main(int argc, char* argv[])
{
    if (argc == 1 || argc > 3)
    {
        std::cerr << "Неверно переданы обязательные параметры: имя файла логирования и уровень логирования по-умолчанию" 
                  << std::endl;
        return 1;
    }
    while (true)
    {
        // f - file, s - socket
        char strategy_number = 0;
        std::cout << "Введите способ логирования(f/s): ";
        std::cin >> strategy_number;

        logger::LoggerStrategy *strategy;
        if (strategy_number == 's')
        {
            strategy = new logger::SocketLoggerStrategy("127.0.0.1", 9000);
            std::cout << ">>> Выбранный способ: сокет\n";
        }
        else
        {
            strategy = new logger::FileLoggerStrategy(argv[1]);
            std::cout << ">>> Выбранный способ: файл\n";
        }

        // Передаем способ логирования и минимальный уровень логирования
        logger::Logger log = (argc == 3)
                                 ? logger::Logger(strategy, toLogLevel(argv[2]))
                                 : logger::Logger(strategy);
        int lvl = 0;
        std::cout << "Введите численный уровень лога: ";
        std::cin >> lvl;
        std::cin.ignore();

        std::string msg;
        std::cout << "Введите сообщение лога: ";
        std::getline(std::cin, msg);
        switch (lvl)
        {
        case 1:
        {
            log.debug() << "Полученное сообщение: " << msg;
            break;
        }
        case 2:
        {
            log.info() << "Полученное сообщение: " << msg;
            break;
        }
        case 3:
        {
            log.warning() << "Полученное сообщение: " << msg;
            break;
        }
        }
        std::cout << "Нажмите любую кнопку для продолжения...";
        std::cin.get();
        system("clear");
    }
}
