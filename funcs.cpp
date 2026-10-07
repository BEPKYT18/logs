#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <chrono>


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
    int64_t NOW = 820454400;//26 years
    int64_t YEAR = 31536000;
    int64_t DAYS28 = 2419200;
    size_t DAY = 86400;
    size_t HOUR = 3600;
    size_t MINUTE = 60;
};

int64_t randint64_t(const int64_t& min,const int64_t& max){
    std::random_device rd;
    std::seed_seq seed{
        rd(), rd(), rd(), rd(),
        static_cast<unsigned>(
            std::chrono::high_resolution_clock::now()
                .time_since_epoch().count())
    };
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int64_t> dist(min, max);

    return dist(gen);
}


//перевод в логи
void SecToYear(int64_t& log_date, Date& D, const Consts& C){
    D.year=(log_date/C.FOURYEARS)*4 + (log_date%C.FOURYEARS)/C.YEAR;
    log_date=(log_date%C.FOURYEARS)%C.YEAR;
}

void SecToMonth(int64_t& log_date, Date& D, const Consts& C){
    size_t monthes[]={2678400, 2419200, 2678400, 2592000, 2678400, 2592000, 2678400, 2678400, 2592000, 2678400, 2592000, 2678400};
    D.month=1;
    if(D.year%4==0){//високосный год
        monthes[1] = C.DAYS28+C.DAY;
        
        while(log_date>=monthes[D.month-1]){
            log_date-=monthes[D.month-1];
            ++D.month;
        }
   
    }
    else{
        monthes[1] = C.DAYS28;
        while(log_date>=monthes[D.month-1]){
            log_date-=monthes[D.month-1];
            ++D.month;
        }
    }
}

void SecToDay(int64_t& log_date, Date& D, const Consts& C){
    D.day=1;
    while(log_date>=C.DAY){
        log_date-=C.DAY;
        ++D.day;
    }
}

void SecToHour(int64_t& log_date, Date& D, const Consts& C){
    D.hour=0;
    while(log_date>=C.HOUR){
        log_date-=C.HOUR;
        ++D.hour;
    }
}

void SecToMinuteAndSec(int64_t& log_date, Date& D, const Consts& C){
    D.minute=0;
    while(log_date>=C.MINUTE){
        log_date-=C.MINUTE;
        ++D.minute;
    }
    D.second=log_date;
}


void log_dateToDate(int64_t& log_date, Date& D, const Consts& C){
    SecToYear(log_date, D, C);
    SecToMonth(log_date, D, C);
    SecToDay(log_date, D, C);
    SecToHour(log_date, D, C);
    SecToMinuteAndSec(log_date, D, C);
}

std::string MakeLog(const Date& D, const std::string& name, const std::string& command, const size_t& code){
    std::string monthes[]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    std::ostringstream oss;
    oss<<D.year<<", "<<monthes[D.month-1]<<' '<<D.day<<", "<<D.hour<<':'<<D.minute<<':'<<D.second<<' '<<name<<' '<<command<<' '<<code;
    return oss.str();
}

//запись в файл

void WriteLog(std::ofstream& fout,const size_t& count, Date& D,
    const std::string* names, const std::string* commands, const size_t* codes, const Consts& C){ 
    for(int i=0;i<count;++i){
        int64_t log_date=randint64_t(C.Y2000, C.Y2000+C.NOW);
        log_dateToDate(log_date, D, C);
        std::string log = MakeLog(D, names[randint64_t(0, sizeof(names)/sizeof(names[0]))], commands[randint64_t(0, sizeof(commands)/sizeof(commands[0]))], codes[randint64_t(0, sizeof(codes)/sizeof(codes[0]))]);
        fout<<log<<'\n';
    }
}