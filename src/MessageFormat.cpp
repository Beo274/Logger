#include "../include/MessageFormat.h"

MessageFormat::MessageFormat(std::string t_msg, std::string t_lvl) : msg(t_msg), msg_lvl(t_lvl)
{
}

MessageFormat::~MessageFormat()
{
}

std::string MessageFormat::format_message()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_tm = std::localtime(&now_time); // или std::gmtime для UTC

    std::ostringstream ss;

    ss << std::put_time(local_tm, "%Y-%m-%d %H:%M:%S") << "  |";

    ss << std::setw(9) << std::right << msg_lvl << "|  ";

    ss << msg << "\n";

    return ss.str();
}

