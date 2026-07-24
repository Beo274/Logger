#include "Statistics.h"

Statistics::~Statistics()
{
    running = false;
}

void Statistics::init(int N, int T)
{
    this->N = N;
    this->T = T;
    running = true;
    last_print = std::chrono::steady_clock::now();


    auto sys_now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(sys_now);
    std::tm now_tm = *std::localtime(&now_c);
    std::cout << "[" << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << "]" << std::endl;
}

Message Statistics::parse_log(std::string str_msg)
{
    // Структура сообщения
    Message message;
    // Временный буфер
    std::string buf;
    // Счетчик черточек
    int dash_counter = 0;

    for (auto s : str_msg)
    {
        // Проверка на разделитель
        if (s == '|')
        {
            
            if (dash_counter == 0) // Если в буфер записалось время
            {
                std::istringstream ss(buf);
                ss >> std::get_time(&message.time, "%Y-%m-%d %H:%M:%S");
                buf = "";

                dash_counter++;

                continue;
            }
            else if (dash_counter == 1) // Если в буфер записан уровено лога
            {
                
                message.lvl += buf;
                buf = "";

                dash_counter++;

                continue;
            }
            dash_counter++;
        }

        if (s == '\n') // Если в буфере само сообщение
        {
            message.msg += buf;
            buf = "";
        }

        if (s == ' ')
        {
            // Пропускаем пробел, если это уровень, либо начало строки, либо пробел после даты
            if (dash_counter == 1 || buf == "" || (dash_counter == 0 && buf.size() == 19))
                continue;
        }

        // Если все хорошо, то добавялем символ в буфер
        buf += s;
    }
    return message;
}

void Statistics::upd_counter_by_level(const Message &message)
{
    if (message.lvl == "DEBUG")
        stat.level_msg_counters["DEBUG"]++;
    if (message.lvl == "INFO")
        stat.level_msg_counters["INFO"]++; 
    if (message.lvl == "WARNING")
        stat.level_msg_counters["WARNING"]++;
}

void Statistics::upd_counter_by_time(Message &message)
{
    std::time_t t = std::mktime(&message.time);
    stat.time_msg_counter.push_back(t);
    while (stat.time_msg_counter.front() < t - 3600)
    {
        std::cout << "Удаление старого времени" << std::endl;
        stat.time_msg_counter.pop_front();
    }
}

void Statistics::upd_counter()
{
    stat.msg_counter++;
}

void Statistics::upd_max(const Message &message)
{
    stat.max_len = (message.msg.length() > stat.max_len) ? message.msg.length() : stat.max_len;
}

void Statistics::upd_min(const Message &message)
{
    stat.min_len = (message.msg.length() < stat.min_len) ? message.msg.length() : stat.min_len;
}

void Statistics::upd_avg(const Message &message)
{
    // Подсчет среднего на основе предыдущего среднего
    stat.av_len = (stat.av_len * stat.msg_counter + message.msg.length()) / (stat.msg_counter + 1);
}

void Statistics::wait() 
{
    while (running) 
    {
        std::this_thread::sleep_for(std::chrono::seconds(T));
        if (changed)
        {
            std::cout << std::endl << "Вызов по таймеру\n";
            print_stat();  
        }  
        if (!running) 
            break;
    }
}

void Statistics::print_stat()
{
    auto now = std::chrono::steady_clock::now();
    last_print = now;
    auto sys_now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(sys_now);
    std::tm now_tm = *std::localtime(&now_c);

    std::cout  << "=== Статистика по полученным сообщениям ==== " << std::endl;

    std::cout << "Минимальная длина: " << stat.min_len << std::endl;
    std::cout << "Максимальная длина: " << stat.max_len << std::endl;
    std::cout << "Средняя длина: " << stat.av_len << std::endl;

    std::cout << std::endl
              << "DEBUG сообщений: " << stat.level_msg_counters["DEBUG"] << std::endl;
    std::cout << "INFO сообщений: " << stat.level_msg_counters["INFO"] << std::endl;
    std::cout << "WARNING сообщений: " << stat.level_msg_counters["WARNING"] << std::endl;

    std::cout << std::endl
              << "Сообщений за последний час: " << stat.time_msg_counter.size() << std::endl
              << std::endl;

    changed = false;
}

void Statistics::add_message(std::string str_message)
{
    if (stat.msg_counter == 0)
    {
        worker = std::thread(&Statistics::wait, this);
    }

    Message message = parse_log(str_message);
    changed = true;
    
    upd_max(message);
    upd_min(message);
    upd_avg(message);
    upd_counter();
    upd_counter_by_level(message);
    upd_counter_by_time(message);

    if (stat.msg_counter == N)
    {
        std::cout << "Вызов по кл-ву\n";
        print_stat();
    }
    
}

Statistics& Statistics::getInstance()
{
    static Statistics instance;
    return instance;
}
