#include <fstream>

struct Date{
    size_t year=0;
    size_t moth=0;
    size_t day=0;
    size_t hour=0;
    size_t minute=0;
    size_t second=0;
};

struct Consts{
    int64_t Y2000 = 63115200000;
    int64_t FOURYEARS = 126230400;
    int64_t NOW = 820454400;
    int64_t YEAR = 31536000;
};

struct Log{
    Date D;
    std::string name;
    std::string command;
    size_t code;
};

void log_dateToDate(const size_t& log_date, Date& D, const Consts& C){
    D.year=log_date/C.FOURYEARS*4 + (log_date%C.FOURYEARS)/C.YEAR;
    
}
