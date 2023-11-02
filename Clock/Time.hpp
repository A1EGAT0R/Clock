#pragma once
#include <string>


namespace Types
{
    enum class Time_type: int8_t
    {
        sec = 1,
        min,
        hour,
        ALL
    };
}
struct Time
{
    
private:
    int16_t hour;
    int16_t  min;
    int16_t  sec;
    bool new_time;

    std::string str_hour;
    std::string str_min;
    std::string str_sec;
    
private:
    void intT_to_stringT();
    void stringT_to_intT();

    void format(Types::Time_type t);

public:
    Time();
    Time(int16_t, int16_t, int16_t);
    
    Time& operator=(const Time&);
    
    bool is_new_time();
    void set_time(int16_t, int16_t, int16_t);
    void set_sec(int16_t);
    void set_min(int16_t);
    void set_hour(int16_t) ;

    void running();


    int16_t get_sec() const;
    int16_t get_min() const;
    int16_t get_hour() const;
    std::string get_str_sec() const noexcept;
    std::string get_str_min() const noexcept;
    std::string get_str_hour() const noexcept;

    void stop();
};
