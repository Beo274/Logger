#include <iostream>
#include <cstdlib>
#include "../include/Logger.h"

int main(int, char **)
{
    logger::Logger log("testlog.txt");

    int lvl = 0;
    std::string msg;
    std::cout << "Введите численный уровень лога: ";
    std::cin >> lvl;
    std::cin.ignore();

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
