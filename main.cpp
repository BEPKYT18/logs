#include <iostream>
#include <ctime>
#include "funcs.cpp"

int main(){
    std::string names [] = {"user", "zhorik", "bobik"};
    std::string commands [] = {"/start", "/end"};
    size_t codes [] = {200, 404, 500};
    srand(time(0));
    std::ofstream fout("system_logs.txt");
    Consts C;
    int64_t log_date=C.Y2000 + rand() % C.NOW;

}