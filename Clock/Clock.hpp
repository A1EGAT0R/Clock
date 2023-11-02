#pragma once

#include "Time.hpp"

class Clock
{
    Time this_clock_time;
    std::string this_clock_name;
    bool next_min;
    bool helper;

    void clear_win() const;

    void save_time();
    Time read_time();

    void save_break_point();
    Time read_break_point();

    void calculate(Time&&, Time&) ;

    void time_run();

    Time get_time() const;

    void set_time(std::string);
    void set_time(int16_t, int16_t, int16_t);
    void set_sec(int16_t);
    void set_min(int16_t);
    void set_hour(int16_t);

    void menu(bool&);
    void set();
    
public:
    Clock();

    Clock& operator =(const Clock&);
    
    void print_time() const;
    void work();
};
