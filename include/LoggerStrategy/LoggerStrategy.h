#ifndef LOGGERCONTEXT_H
#define LOGGERCONTEXT_H

#pragma once

#include <string>



    class LoggerStrategy
    {
    public:
        LoggerStrategy();
        ~LoggerStrategy();

        virtual void write(const std::string& message) = 0;

    private:

    };


#endif