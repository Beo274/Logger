#include <iostream>
#include <cstdlib>
#include "../include/Logger.h"
#include "../include/LoggerStrategy/FileLoggerStrategy.h"
#include "../include/LoggerStrategy/SocketLoggerStrategy.h"

int main(int, char **)
{
    logger::Logger log("testlog.txt", logger::LogLevel::INFO);

    // 0 - file, 1 - socket
    int strategy = 0;
    std::cout << "Введите способ логирования: ";
    std::cin >> strategy;
    if (strategy == 0) 
    {
        auto *fileLogStrategy = new logger::FileLoggerStrategy("testlog.txt");
        log.setStrategy(*fileLogStrategy);
    }
    else
    {
        auto *socketLogStrategy = new logger::SocketLoggerStrategy("127.0.0.1", 9000);
        log.setStrategy(*socketLogStrategy);
    }

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
