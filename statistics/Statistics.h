#ifndef STATISTICS_H
#define STATISTICS_H

#pragma once
#include <mutex>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

struct Stat
{
    std::map<std::string, int> level_msg_counters = {
        {"DEBUG",   0},
        {"INFO",    0},
        {"WARNING", 0}
    };
    std::vector<tm> time_msg_counter = {};
    int msg_counter                  = 0;
    int hour_msg_counter             = 0;
    int av_len                       = 0;
    int max_len                      = 0;
    int min_len                      = INT32_MAX;
};

struct Message
{
    tm time         = {};
    std::string lvl = "";
    std::string msg = "";
};

class Statistics
{
public:
    static Statistics& getInstance();
    ~Statistics();
    void init(int N, int T);

    Message parse_log(std::string str_msg);

    int upd_counter_by_level(Message message);
    int upd_counter_by_time(Message message);
    int upd_counter(Message message);
    int upd_max(Message message);
    int upd_min(Message message);

    void add_message(std::string message);

    Statistics(Statistics &other) = delete;
    void operator=(const Statistics&) = delete;

private:
    Statistics()  = default;

    std::mutex locker;

    int N;
    int T;

    Stat stat;
    
};

#endif