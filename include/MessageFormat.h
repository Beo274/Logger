#ifndef STRINGFORMAT_H
#define STRINGFORMAT_H

#pragma once

#include <sstream>
#include <iomanip>
#include <chrono>
#include <string>

class MessageFormat
{
public:
    MessageFormat(std::string, std::string);
    ~MessageFormat();

    std::string format_message();

private:
    std::string msg;
    std::string msg_lvl;
    std::string out;

};

#endif