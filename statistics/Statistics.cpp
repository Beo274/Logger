#include "Statistics.h"

Statistics::~Statistics()
{

}

void Statistics::init(int N, int T)
{
    std::lock_guard<std::mutex> lock(locker);
    this->N = N;
    this->T = T;
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

// int Statistics::upd_counter_by_level(Message message)
// {
    
// }

// int Statistics::upd_counter_by_time(Message message)
// {
    
// }

// int Statistics::upd_counter(Message message)
// {
    
// }

int Statistics::upd_max(Message message)
{
    return stat.max_len = (message.msg.length() > stat.max_len) ? message.msg.length() : stat.max_len;
}

int Statistics::upd_min(Message message)
{
    return stat.min_len = (message.msg.length() < stat.min_len) ? message.msg.length() : stat.min_len;
}

void Statistics::add_message(std::string str_message)
{
    Message message = parse_log(str_message);
    
    upd_max(message);
    upd_min(message);
    std::cout << "Сообщегние = " << message.msg << std::endl;
    std::cout << "Минимальная длина = " << stat.min_len << std::endl;
    std::cout << "Максимальная длина = " << stat.max_len << std::endl;




    stat.msg_counter++;

    
}

Statistics& Statistics::getInstance()
{
    static Statistics instance;
    return instance;
}
