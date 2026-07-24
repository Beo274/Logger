#ifndef RECEIVER_H
#define RECEIVER_H

#pragma once

#include <unistd.h>     
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include "Statistics.h"

class Receiver
{
public:
    Receiver(const std::string ip, const int port);
    ~Receiver();

    void start_listening(const int port);
    void stop();

private:
    int server_fd = -1;
    int client_fd = -1;
    bool is_running = false;

    void close_client();
    void close_server();

};

#endif