#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <fstream>
//==================================================================================TIME_DEFINITON_BEGIN
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
    unsigned short hour;
    unsigned short  min;
    unsigned short  sec;
    bool new_time;
    
    std::string str_hour;
    std::string str_min;
    std::string str_sec;
    
    void intT_to_stringT();
    void stringT_to_intT();
    
    void format(Time_type&& t);
    
public:
    bool is_new_time();
    void set_time(unsigned short, unsigned short, unsigned short);
    void set_sec(unsigned short);
    void set_min(unsigned short);
    void set_hour(unsigned short);
    
    void running();
    
    Time();
    Time(unsigned short, unsigned short, unsigned short);
    
    unsigned short get_sec() const;
    unsigned short get_min() const;
    unsigned short get_hour() const;
    std::string get_str_sec() const;
    std::string get_str_min() const;
    std::string get_str_hour() const;
    
    void stop();
    Time* get_time();
    
    Time& operator=(Time&);
};
//==================================================================================TIME_DEFINITON_END


//==================================================================================CLOCK_DEFINITON_BEGIN
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
    Time& read_time();
    
    void save_break_point();
    Time&& read_break_point();
    
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
    
    void print_time();
    void work();
};
//==================================================================================CLOCK_DEFINITON_END


//==================================================================================TIME_INIT_BEGIN
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
Time::Time(unsigned short s, unsigned short m, unsigned short h):hour(h), min(m), sec(s)
{
    new_time = 0;
    intT_to_stringT();
}

void
Time::set_sec(unsigned short sec)
{
    this->sec = sec;
    this->str_sec = std::to_string(sec);
    format(Time_type::sec);
}
void
Time::set_min(unsigned short min)
{
    this->min = min;
    this->str_min = std::to_string(min);
    format(Time_type::min);
}
void
Time::set_hour(unsigned short hour)
{
    this->hour = hour;
    this->str_hour = std::to_string(hour);
    format(Time_type::hour);
}

void
Time::set_time(unsigned short hour, unsigned short min, unsigned short sec)
{
    //new_time = 1;
    this->set_hour(hour);
    this->set_min(min);
    this->set_sec(sec);
}

unsigned short
Time::get_sec() const
{
    return sec;
}
unsigned short
Time::get_min() const
{
    return min;
}
unsigned short
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
Time::operator=(Time &t)
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
    
    format(Time_type::ALL);
}

void
Time::format(Time::Time_type&& t)
{
    switch (t) {
        case Time::Time_type::sec:
            if(str_sec.size() == 1)
                str_sec = '0' +str_sec;
            break;
        case Time::Time_type::min:
            if(str_min.size() == 1)
                str_min = '0' +str_min;
            break;
        case Time::Time_type::hour:
            if(str_hour.size() == 1)
                str_hour = '0' +str_hour;
            break;
        case Time::Time_type::ALL:
            format(Time::Time_type::sec);
            format(Time::Time_type::min);
            format(Time::Time_type::hour);
            break;
        default:
            std::cout<<"WRONG TYPE. I'll do 'ALL'\n";
            format(Time::Time_type::ALL);
            break;
    }
         
}
//==================================================================================TIME_INIT_END


//==================================================================================CLOCK_INIT_START

//==================================================================================CLOCK_INIT======SET_TIME
void
Clock::set_sec(unsigned short s) noexcept
{
    this_clock_time.set_sec(s);
}
void
Clock::set_min(unsigned short m) noexcept
{
    this_clock_time.set_min(m);
}
void
Clock::set_hour(unsigned short h) noexcept
{
    this_clock_time.set_hour(h);
}
void
Clock::set_time(unsigned short h, unsigned short m, unsigned short s) noexcept
{
    this_clock_time.set_time(h, m, s);
}

void
Clock::set_time(std::string now) noexcept
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
Time*
Clock::get_time() noexcept
{
    return &this_clock_time;
}
//==================================================================================CLOCK_INIT======GET_TIME

//==================================================================================CLOCK_INIT======CONSTRUCT
Clock::Clock(): this_clock_name("CLOCK")
{
    helper = 1;
    next_min = 1;

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
Clock::print_time()
{
    clear_win();
    std::cout<< this_clock_time.get_str_hour() << ":" << this_clock_time.get_str_min()<<"\n";
}

void
Clock::time_run() noexcept
{
    this_clock_time.running();
}

void
Clock::work()
{
    bool work_on = true;
    std::thread timer(&Clock::time_run, this);
    
    std::thread stopping([&]()
                         {
        menu(work_on);
    });
    while(work_on)
    {
        if(next_min||this_clock_time.is_new_time())
        {
            next_min = 0;
            print_time();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        if(helper)
        {
            std::cout<< "\nWhich function I have?\n 1)STOP\n 2)SET(3 int arguments)\n 3)SET(argument 'NOW')\n 4)HELP\n";
            helper = 0;
        }
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
Time&
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

Time&&
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
Clock::calculate(Time &&break_point, Time& ret) noexcept
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
        }
        else if(command == "STOP")
        {
            stop = 0;
            break;
        }
        else if (command == "HELP")
        {
            helper = 1;
            next_min = 1;
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
    this->next_min = 1;

}
//==================================================================================CLOCK_INIT======MENU

//==================================================================================CLOCK_INIT_END
int main() {
    Clock ck;
    ck.work();
    return 0;
}
