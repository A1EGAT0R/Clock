#include "Time.hpp"
#include <chrono>
#include <thread>
#include <time.h>
#include <iostream>

bool
Time::is_new_time()
{
    if(new_time)
    {
        new_time = 0;
        return 1;
    }
    else
        return 0;
}
Time::Time(): hour(0), min(0), sec(0)
{
    new_time = 0;
    intT_to_stringT();
}
Time::Time(int16_t s, int16_t m, int16_t h):hour(h), min(m), sec(s)
{
    new_time = 0;
    intT_to_stringT();
}

void
Time::set_sec(int16_t sec)
{
    this->sec = sec;
    this->str_sec = std::to_string(sec);
    format(Types::Time_type::sec);
}
void
Time::set_min(int16_t min)
{
    this->min = min;
    this->str_min = std::to_string(min);
    format(Types::Time_type::min);
}
void
Time::set_hour(int16_t hour)
{
    this->hour = hour;
    this->str_hour = std::to_string(hour);
    format(Types::Time_type::hour);
}

void
Time::set_time(int16_t hour,int16_t min, int16_t sec)
{
    new_time = 1;
    this->set_hour(hour);
    this->set_min(min);
    this->set_sec(sec);
}

int16_t
Time::get_sec() const
{
    return sec;
}
int16_t
Time::get_min() const
{
    return min;
}
int16_t
Time::get_hour() const
{
    return hour;
}

std::string
Time::get_str_sec() const
{
    return str_sec;
}
std::string
Time::get_str_min() const
{
    return str_min;
}
std::string
Time::get_str_hour() const
{
    return str_hour;
}

void
Time::running()
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        sec++;
        if(sec >= 60)
        {
            sec-=60;
            min++;
            new_time = 1;
        }

        if(min >= 60)
        {
            min-=60;
            hour++;
            new_time = 1;
        }
        if(hour>=24)
        {
            new_time = 1;
            hour-=24;
        }

        intT_to_stringT();
    }
}

Time&
Time::operator=(const Time &t)
{
    this->set_time(t.get_hour(), t.get_min(), t.get_sec());

    return *this;
}

void
Time::stringT_to_intT()
{
    this->sec = std::stoi(str_sec);
    this->min = std::stoi(str_min);
    this->hour = std::stoi(str_hour);
}
void
Time::intT_to_stringT()
{
    this->str_sec = std::to_string(sec);
    this->str_min = std::to_string(min);
    this->str_hour = std::to_string(hour);

    format(Types::Time_type::ALL);
}

void
Time::format(Types::Time_type t)
{
    switch (t) {
    case Types::Time_type::sec:
        if(str_sec.size() == 1)
            str_sec = '0' +str_sec;
        break;
    case Types::Time_type::min:
        if(str_min.size() == 1)
            str_min = '0' +str_min;
        break;
    case Types::Time_type::hour:
        if(str_hour.size() == 1)
            str_hour = '0' +str_hour;
        break;
    case Types::Time_type::ALL:
        format(Types::Time_type::sec);
        format(Types::Time_type::min);
        format(Types::Time_type::hour);
        break;
    default:
        std::cout<<"WRONG TYPE. I'll do 'ALL'\n";
        format(Types::Time_type::ALL);
        break;
    }

}

