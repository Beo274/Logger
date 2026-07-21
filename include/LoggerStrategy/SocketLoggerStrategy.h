#ifndef SOCKETLOGGER_H
#define SOCKETLOGGER_H

#pragma once

#include "LoggerStrategy.h"

namespace logger 
{
    class SocketLoggerStrategy : public LoggerStrategy
    {
    public:
        SocketLoggerStrategy();
        ~SocketLoggerStrategy();

    private:

    };
}

#endif