#include "funcs.cpp"

int main(){
    
    std::string names [] = {"user", "zhorik", "bobik"};
    std::string commands [] = {"/start", "/end"};
    size_t codes [] = {200, 404, 500};
    std::ofstream fout("system_logs.txt", std::ios::out | std::ios::app);
    Consts C;
    Date D;
    size_t count=1;
    WriteLog(fout,count,D,names,commands,codes,C);
    //std::cout<<names[randint64_t(0, sizeof(names)/sizeof(names[0])-1)];
}