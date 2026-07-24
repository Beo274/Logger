#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <random>
#include "../include/Logger.h"
#include "../include/LoggerStrategy/LoggerStrategy.h"
#include "../include/LoggerStrategy/FileLoggerStrategy.h"
#include "../include/LoggerStrategy/SocketLoggerStrategy.h"

LogLevel toLogLevel(std::string str_lvl)
{
    if (str_lvl == "DEBUG")    return LogLevel::DEBUG;  
    if (str_lvl == "INFO")    return LogLevel::INFO; 
    if (str_lvl == "WARNING")  return LogLevel::WARNING;
    // По умолчанию 
    return LogLevel::NO;
}

void load()
{
    const std::vector<std::string> resources = {"Cache", "Database", "Cookies", "Config"};
    
    // Подготовка рандомайзера
    std::random_device rd;
    std::mt19937 gen(rd());

    // Указание диапазонов
    std::uniform_int_distribution<> dist_for_i(0, 3);
    std::uniform_int_distribution<> dist_for_percent(15, 30);

    // Выбор ресурса
    int i = dist_for_i(gen);
    std::string res = resources.at(i);

    // Выбор начального значения
    int percent = dist_for_percent(gen);

    while (percent < 100)
    {
        // Вывод текущего процента загрузки в лог с указанием потока
        Logger::getInstance().info() << res << ": загрузка " << percent << "%" 
                        << " Поток #" << std::this_thread::get_id();

        // Увеличения процента загрузки
        int step = dist_for_percent(gen);
        percent += step;

        // Условие завершения и вывод в лог сообщения о завершении
        if (percent >= 100)
        {
            Logger::getInstance().info() << "Загрузка завершена: " << res 
                        << " Поток #" << std::this_thread::get_id();
        }
    }

}

void write_log(std::string msg, char lvl)
{
    // Записываем сообщение в лог
    switch (lvl)
        {
        case 'd':
        {
            Logger::getInstance().debug() << "Полученное сообщение: " << msg 
                        << " Поток #" << std::this_thread::get_id();
            break;
        }
        case 'i':
        {
            Logger::getInstance().info() << "Полученное сообщение: " << msg 
                        << " Поток #" << std::this_thread::get_id();
            break;
        }
        case 'w':
        {
            Logger::getInstance().warning() << "Полученное сообщение: " << msg 
                        << " Поток #" << std::this_thread::get_id();
            break;
        }
        }

        // Дополнительная логика: имитация загрузки ресурсов
        if (Logger::getLevel() <= LogLevel::INFO)
            load();
}


int main(int argc, char* argv[])
{
    if (argc == 1 || argc > 3)
    {
        std::cerr << "Неверно переданы обязательные параметры: имя файла логирования и уровень логирования по-умолчанию" 
                  << std::endl;
        return 1;
    }

    std::cout << "Для выхода введите 'q'\n";
    // f - file, s - socket
    char strategy_number = 0;
    std::cout << "Введите способ логирования(f/s): ";
    std::cin >> strategy_number;

    LoggerStrategy *strategy;
    if (strategy_number == 's')
    {
        strategy = new SocketLoggerStrategy("127.0.0.1", 9000);
        std::cout << ">>> Выбранный способ: сокет\n";
    }
    else if (strategy_number == 'q')
    {
        return 0;
    }
    else
    {
        strategy = new FileLoggerStrategy(argv[1]);
        std::cout << ">>> Выбранный способ: файл\n";
    }

    while (true)
    {
        

        // Передаем способ логирования и минимальный уровень логирования
        if (argc == 3)
        {
            Logger::getInstance().init(strategy, toLogLevel(argv[2]));
        }
        else
        {
            Logger::getInstance().init(strategy);
        }
        char lvl = 0;
        std::cout << "Введите численный уровень лога(d/i/w): ";
        std::cin >> lvl;
        std::cin.ignore();

        if (lvl == 'q') return 0;
        if (lvl != 'd' && lvl != 'D'
         && lvl != 'i' && lvl != 'I'
         && lvl != 'w' && lvl != 'W') 
        {
            std::cout << "Введен неверный уровень\n";
            return 0;
        }
        std::string msg;
        std::cout << "Введите сообщение лога: ";
        std::getline(std::cin, msg);

        if (msg == "q") return 0;

        
        int n = 100000;
        while (n > std::thread::hardware_concurrency() || n < 1)
        {
            std::cout << "Введите, сколько раз вы хотите записать это сообщение (Максимум:  " << std::thread::hardware_concurrency() << "):";
            std::cin >> n;
            std::cin.clear();
            if (n > std::thread::hardware_concurrency() || n < 1)
                std::cout << ">>> Неверное число. Диапазон 1 - " << std::thread::hardware_concurrency() << std::endl;
            
        }
        
        // Создаем n потоков, которые записывают одно и то же сообщение
        std::vector<std::thread> threads;
        for (int i = 0; i < n; i++)
            threads.push_back(std::thread(write_log, msg, lvl));


        // Дожидаемся все потоки
        for (auto& thread : threads)
        {
            if (thread.joinable())
                thread.join();
        }
        
        std::cin.ignore();
        std::cout << "Нажмите Enter для продолжения...";
        std::cin.get();

        system("clear");
    }
}
