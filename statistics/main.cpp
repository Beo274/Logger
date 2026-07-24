#include <iostream>
#include "Receiver.h"
#include "Statistics.h"

int main(int argc, char** argv)
{
    if (argc < 5) 
    {
        std::cerr << "Неверное введены параметры программы, нужный формат: IP-адрес, порт, кол-во сообщений N, кол-во секунд T\n";
    }
    std::string addr = argv[1];
    int port = std::stoi(argv[2]);
    int N = std::stoi(argv[3]);
    int T = std::stoi(argv[4]);

    Statistics::getInstance().init(N,T);

    Receiver receiver(addr, port);
    receiver.start_listening(port);
}