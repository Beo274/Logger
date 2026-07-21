#include "../../include/LoggerStrategy/SocketLoggerStrategy.h"
#include <iostream>

namespace logger 
{
    SocketLoggerStrategy::SocketLoggerStrategy(std::string t_ip, int t_port) : ip(t_ip), port(t_port)
    {
        connect();
    }

    SocketLoggerStrategy::~SocketLoggerStrategy()
    {
        disconnect();
    }

    bool SocketLoggerStrategy::connect()
    {
        // Проверяю отстутствие подключения
        if (socket_fd != -1) 
        {
            return true;
        }

        // Создаю TCP-сокет 
        socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0)
        {
            std::cerr << "Ошибка создания сокета!\n";
            return false;
        }

        // Заполняю данные сервера
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        if (::inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0)
        {
            std::cerr << "Неверный IP адрес: " << ip << std::endl;
            disconnect();
            return false;
        }

        // Подключаюсь к серверу
        if (::connect(socket_fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) < 0)
        {
            std::cerr << "Не удалось подключиться к " << ip << ":" << port << std::endl;
            disconnect();
            return false;
        }

        return true;
    }

     void SocketLoggerStrategy::disconnect()
    {
        if (socket_fd != -1) 
        {
            ::close(socket_fd); 
            socket_fd = -1;
        }
    }

    void SocketLoggerStrategy::write(std::string msg)
    {
        if (socket_fd == -1 && !connect()) 
        {
            return;
        }

        msg += "\n";
        const char *buffer = msg.c_str();
        size_t bytes_left = msg.size();
        size_t total_sent = 0;

        // Отправка в цикле
        while (total_sent < bytes_left)
        {
            ssize_t sent = ::send(socket_fd, buffer + total_sent, bytes_left - total_sent, MSG_NOSIGNAL);

            if (sent < 0)
            {
                std::cerr << "Ошибка отправки данных. Соединение потеряно.\n";
                disconnect(); 
                break;
            }

            total_sent += static_cast<size_t>(sent);
        }
    }
}