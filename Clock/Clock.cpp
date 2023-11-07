#include "Clock.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
void
Clock::set_time(int16_t h, int16_t m, int16_t s)
{
    this_clock_time.set_time(h, m, s);
}

void
Clock::set_time(std::string now)
{
    if(now == "NOW")
    {
        time_t now = time(0);
        tm *lt(localtime(&now));
        this_clock_time.set_time(lt->tm_hour, lt->tm_min, lt->tm_sec);
    }
    else
        std::cout<<"WRONG COMMAND\n";
}

//==================================================================================CLOCK_INIT======SET_TIME

//==================================================================================CLOCK_INIT======GET_TIME
Time
Clock::get_time() const
{
    return this_clock_time;
}
//==================================================================================CLOCK_INIT======GET_TIME

//==================================================================================CLOCK_INIT======CONSTRUCT
Clock::Clock(): this_clock_name("CLOCK")
{
    helper = 1;

    std::ifstream ist(this->this_clock_name + ".clck");
    if(ist)
    {
        this_clock_time = read_time();

        ist.close();
    }
    else
    {
        time_t now = time(0);
        tm *lt(localtime(&now));
        this_clock_time.set_time(lt->tm_hour, lt->tm_min, lt->tm_sec);
    }
}
//==================================================================================CLOCK_INIT======CONSTRUCT

//==================================================================================CLOCK_INIT======WORK_&_HELP
void
Clock::print_time() const noexcept
{
    clear_win();
    std::cout<< this_clock_time.get_str_hour() << ":" << this_clock_time.get_str_min()<<"\n";
}

void
Clock::clear_win() const noexcept
{
    std::cout << "\033[0d\033[2J";
}
void
Clock::time_run() 
{
    this_clock_time.running();
}

void
Clock::work()
{
    std::unique_lock<std::mutex> u_lock(sign);
    bool work_on = true;
    std::thread timer(&Clock::time_run, this);

    std::thread stopping([&]()
                         {
                             menu(work_on);
                         });
    while(work_on)
    {
        print_time();
        if(helper)
        {
            std::cout<< "\nWhich function I have?\n 1)STOP\n 2)SET(3 int arguments)\n 3)SET(argument 'NOW')\n 4)HELP\n";
            helper = 0;
        }
        time_changer.wait(u_lock);
    }
    stopping.detach();
    timer.detach();

    save_time();
}
//==================================================================================CLOCK_INIT======WORK_&_HELP

//==================================================================================CLOCK_INIT======SAVE
void
Clock::save_time()
{
    std::ofstream ost;
    ost.open(this_clock_name + ".clck");

    if(ost)
    {
        ost << this_clock_time.get_str_sec() << '\n';
        ost << this_clock_time.get_str_min()<< '\n';
        ost << this_clock_time.get_str_hour();
    }
    else
        throw 0;

    save_break_point();

    ost.close();
}

void
Clock::save_break_point()
{
    std::ofstream ost;
    ost.open(this_clock_name + "BP" + ".clck");

    if(ost)
    {
        time_t now = time(0);
        tm *lt(localtime(&now));

        ost<< lt->tm_sec<<'\n';
        ost<< lt->tm_min<<'\n';
        ost<< lt->tm_hour<<'\n';
    }
    else
        throw 0;

    ost.close();
}
//==================================================================================CLOCK_INIT======SAVE

//==================================================================================CLOCK_INIT======READ
Time
Clock::read_time()
{
    std::ifstream ist(this_clock_name + ".clck");
    if(!ist)
        throw 0;

    std::string sec; std::getline(ist, sec);
    std::string min; std::getline(ist, min);
    std::string hour; std::getline(ist, hour);

    Time ret(std::stoi(sec), std::stoi(min), std::stoi(hour));

    calculate(read_break_point(), ret);

    return ret;
}
Time
Clock::read_break_point()
{
    std::ifstream istB(this_clock_name + "BP" + ".clck");
    if(!istB)
        throw 0;

    std::string sec; std::getline(istB, sec);
    std::string min; std::getline(istB, min);
    std::string hour; std::getline(istB, hour);

    return Time(std::stoi(sec), std::stoi(min), std::stoi(hour));
}

void
Clock::calculate(Time&& break_point, Time& ret)
{
    time_t now = time(0);
    tm *lt(localtime(&now));

    int corr_s = ret.get_sec() + lt->tm_sec - break_point.get_sec();
    int corr_m = ret.get_min() + lt->tm_min - break_point.get_min();
    int corr_h = ret.get_hour() + lt->tm_hour- break_point.get_hour();

    if(corr_s>59)
    {
        corr_s-=60;
        corr_m++;
    }
    else if(corr_s<0)
    {
        corr_s+=60;
        corr_m--;
    }

    if(corr_m>59)
    {
        corr_m-=60;
        corr_h++;
    }
    else if(corr_m<0)
    {
        corr_m+=60;
        corr_h--;
    }

    if(corr_h>23)
        corr_h-=24;
    else if(corr_h<0)
        corr_h+=24;



    ret.set_time(corr_h, corr_m, corr_s);
}
//==================================================================================CLOCK_INIT======READ


//==================================================================================CLOCK_INIT======MENU
void
Clock::menu(bool& stop)
{
    std::string command;

    while(true)
    {
        std::cin>>command;
        if(command == "SET")
        {
            set();
            this_clock_time.throw_update();
        }
        else if(command == "STOP")
        {
            stop = 0;
            this_clock_time.throw_update();
            break;
        }
        else if (command == "HELP")
        {
            helper = 1;
            this_clock_time.throw_update();
        }

    }
}

void
Clock::set()
{
    std::cout<< "Arguments: \n";

    std::string s;
    int time[3] = {99,99,99};
    std::cin>>s;

    if(s == "NOW")
        set_time("NOW");
    else
    {
        for (int i = 0; i<3; ++i) {
            bool stop = 1;
            while(stop)
            {
                for (char c : s) {
                    if(c>'9'||c<'0')
                    {
                        std::cin.clear();
                        std::cin.ignore(32767, '\n');

                        std::cout<< "INPUT ERROR. Print again\n";
                        std::cin>>s;
                        stop = 1;
                        break;
                    }
                    stop = 0;
                }
            }
            time[i] = std::stoi(s);
            if(i<2)
            {
                std::cin>>s;
            }
        }

        this_clock_time.set_time(time[0], time[1], time[2]);
    }
}

//==================================================================================CLOCK_INIT======OPERATOR

Clock&
Clock::operator=(const Clock &copyClock)
{
    this_clock_time = copyClock.this_clock_time;
    this_clock_name= copyClock.this_clock_name;
    helper = copyClock.helper;
    
    return *this;
}


