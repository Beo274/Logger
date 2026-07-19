#include <iostream>
#include <cstdlib>
#include "../include/Logger.h"

int main(int, char**){
    logger::Logger log("testlog.txt", logger::LogLevel::INFO);

    // while (true)
    // {
        int lvl = 0;
        std::string msg;
        std::cout << "Введите численный уровень лога: ";
        std::cin >> lvl;
        std::cin.ignore(); 

        std::cout << "Введите сообщение лога: ";
        std::getline(std::cin, msg);
        switch(lvl)
        {
            case 0:
            {
                log.debug(msg);
                break;
            }
            case 1:
            {
                log.info(msg);
                break;
            }
            case 2:
            {
                log.warning(msg);
                break;
            }
        }
        // system("clear");
    //}   
    
}
