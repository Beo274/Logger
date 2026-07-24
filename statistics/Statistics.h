#pragma once
#include <mutex>
#include <map>
#include <deque>
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
    std::deque<time_t> time_msg_counter = {};
    int msg_counter                  = 0;
    float av_len                     = 0;
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

    void upd_counter_by_level(const Message &message);
    void upd_counter_by_time(Message &message);
    void upd_counter();
    void upd_max(const Message &message);
    void upd_min(const Message &message);
    void upd_avg(const Message &message);

    void print_stat();

    void add_message(std::string message);

    Statistics(Statistics &other) = delete;
    void operator=(const Statistics&) = delete;

private:
    Statistics()  = default;

    std::mutex locker;

    int N;
    int T;

    bool changed;

    Stat stat;
    
};