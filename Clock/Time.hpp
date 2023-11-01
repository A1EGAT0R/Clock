#pragma once
#include <string>
#include <chrono>
#include <thread>
#include <time.h>
#include <iostream>

struct Time
{
private:
    enum class Time_type: unsigned short
    {
        sec = 1,
        min,
        hour,
        ALL
    };
private:
    unsigned short hour;
    unsigned short  min;
    unsigned short  sec;
    bool new_time;

    std::string str_hour;
    std::string str_min;
    std::string str_sec;
    
private:
    void intT_to_stringT();
    void stringT_to_intT();

    void format(Time_type&& t);

public:
    Time();
    Time(unsigned short, unsigned short, unsigned short);
    
    Time& operator=(const Time&);
    
    bool is_new_time();
    void set_time(unsigned short, unsigned short, unsigned short);
    void set_sec(unsigned short);
    void set_min(unsigned short);
    void set_hour(unsigned short);

    void running();


    unsigned short get_sec() const;
    unsigned short get_min() const;
    unsigned short get_hour() const;
    std::string get_str_sec() const;
    std::string get_str_min() const;
    std::string get_str_hour() const;

    void stop();
    Time* get_time();
};
