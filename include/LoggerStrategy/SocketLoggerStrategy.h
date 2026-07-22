#ifndef SOCKETLOGGER_H
#define SOCKETLOGGER_H

#pragma once

#include "LoggerStrategy.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

namespace logger 
{
    class SocketLoggerStrategy : public LoggerStrategy
    {
    public:
        SocketLoggerStrategy(std::string ip, int port);
        ~SocketLoggerStrategy();

        void write(std::string msg) override;

    private:
        bool connect();
        void disconnect();

        std::string ip;
        int port;
        int socket_fd = -1;
    };   
}

#endif