#include "Receiver.h"

Receiver::Receiver(const std::string ip, const int port)
{
    // Создаем сокет
    server_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        throw std::runtime_error("Ошибка создания сокета");
    }

    // Включаем SO_REUSEADDR, чтобы порт освобождался мгновенно
    int opt = 1;
    ::setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Настраиваем адрес
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (::inet_pton(AF_INET, ip.c_str(), &address.sin_addr) <= 0) {
        close_server();
        throw std::runtime_error(">>> Неверный IP-адрес сервера: " + ip);
    }

    // Привязываем сокет 
    if (::bind(server_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
        close_server();
        throw std::runtime_error("Ошибка привязки к порту");
    }

    // Переводим в режим прослушивания
    if (::listen(server_fd, 5) < 0) {
        close_server();
        throw std::runtime_error("Ошибка чтения");
    }

    is_running = true;
}

Receiver::~Receiver()
{
    stop();
}

void Receiver::start_listening(const int port)
{
    std::cout << ">>> Ожидание подключения на порту " << port << "...\n";

    while (is_running) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);

        client_fd = ::accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);
        
        if (client_fd < 0) {
            if (!is_running) break;
            continue;
        }

        std::cout << ">>> Клиент подключился\n";

        char buffer[1024];
        while (is_running) {
            std::memset(buffer, 0, sizeof(buffer));
            ssize_t bytes_read = ::recv(client_fd, buffer, sizeof(buffer) - 1, 0);

            if (bytes_read > 0) {
                // std::cout << std::string_view(buffer, bytes_read) << std::flush;
                Statistics::getInstance().add_message(buffer);
            } 
            else if (bytes_read == 0) {
                std::cout << ">>> Клиент закрыл соединение.\n";
                break; 
            } 
            else {
                break;
            }
        }
        close_client();
    }
}

void Receiver::stop() 
{
    is_running = false;
    close_client();
    close_server();
}

void Receiver::close_client()
{
    if (client_fd >= 0) 
    {
        ::shutdown(client_fd, SHUT_RDWR); 
        ::close(client_fd);
        client_fd = -1;
    }
}

void Receiver::close_server()
{
    if (server_fd >= 0) 
    {
        ::close(server_fd);
        server_fd = -1;
    }
}