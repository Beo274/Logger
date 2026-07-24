#ifndef RECEIVER_H
#define RECEIVER_H

#pragma once

#include <unistd.h>     
#include <sys/socket.h> 
#include <netinet/in.h>
#include <iostream>
#include <cstring>

class Receiver
{
public:
    Receiver();
    ~Receiver();

    void start_listening();
    void stop();

private:
    const int PORT = 9000;
    const size_t BUFFER_SIZE = 1024;

    int server_fd = -1;
    int client_fd = -1;
    bool is_running = false;

    void close_client();
    void close_server();

};

#endif