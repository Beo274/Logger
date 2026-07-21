#ifndef LOGGERCONTEXT_H
#define LOGGERCONTEXT_H

#pragma once

#include <string>

namespace logger {

    class LoggerStrategy
    {
    public:
        LoggerStrategy();
        ~LoggerStrategy();

        virtual void write(std::string) = 0;

    private:

    };
}

#endif