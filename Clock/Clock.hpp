#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include "Time.hpp"

class Clock
{
    Time this_clock_time;
    std::string this_clock_name;
    bool next_min;
    bool helper;

    void clear_win() {
        std::cout << "\033[0d\033[2J";
    }


    void set_time (Time& t) noexcept;

    void save_time();
    Time read_time();

    void save_break_point();
    Time read_break_point();

    void calculate(Time&&, Time&) noexcept ;

    void time_run() noexcept ;

    Time* get_time() noexcept ;

    void set_time(std::string) noexcept ;
    void set_time(unsigned short, unsigned short, unsigned short) noexcept ;
    void set_sec(unsigned short) noexcept ;
    void set_min(unsigned short) noexcept ;
    void set_hour(unsigned short) noexcept ;

    void menu(bool&);
    void set();
    
public:
    Clock();

    Clock& operator =(const Clock&);
    
    void print_time();
    void work();
};
