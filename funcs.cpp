#include <fstream>

//структуры
struct Date{
    size_t year=0;
    size_t month=0;
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
    int64_t DAYS28 = 2419200;
    size_t DAY = 86400;
    size_t HOUR = 3600;
    size_t MINUTE = 60;
};

struct Log{
    Date D;
    std::string name;
    std::string command;
    size_t code;
};


//перевод в логи
void SecToYear(const size_t& log_date, Date& D, const Consts& C){
    D.year=log_date/C.FOURYEARS*4 + (log_date%C.FOURYEARS)/C.YEAR;
}

void SecToMonth(size_t& log_date, Date& D, const Consts& C, size_t* monthes){
    log_date%=D.year;
    if(D.year%4==3){//високосный год
        monthes[1] = C.DAYS28+C.DAY;
        D.month=1;
        while(log_date>=C.DAYS28+C.DAY){
            log_date-=monthes[D.month-1];
            ++D.month;
        }
   
    }
    else{
        monthes[1] = C.DAYS28;
        while(log_date>=C.DAYS28){
            log_date-=monthes[D.month-1];
            ++D.month;
        }
    }
}

void SecToDay(size_t& log_date, Date& D, const Consts& C){
    log_date%=D.month;
    D.day=1;
    while(log_date>=C.DAY){
        log_date-=C.DAY;
        ++D.day;
    }
}

void SecToHour(size_t& log_date, Date& D, const Consts& C){
    log_date%=D.day;
    D.hour=0;
    while(log_date>=C.HOUR){
        log_date-=C.HOUR;
        ++D.hour;
    }
}

void SecToMinute(size_t& log_date, Date& D, const Consts& C){
    log_date%=D.hour;
    D.minute=0;
    while(log_date>=C.MINUTE){
        log_date-=C.MINUTE;
        ++D.minute;
    }
}

void SecToSecond(size_t& log_date, Date& D, const Consts& C){
    log_date%=D.minute;
    D.second=log_date;
}

void log_dateToDate(size_t& log_date, Date& D, const Consts& C,  size_t* monthes){
    SecToYear(log_date, D, C);
    SecToMonth(log_date, D, C, monthes);
    SecToDay(log_date, D, C);
    SecToHour(log_date, D, C);
    SecToMinute(log_date, D, C);
    SecToSecond(log_date, D, C);
}
