#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include "system_monitor/system_monitor.hpp"

int main(){
    std::string command;
    std::string name = getenv("USER");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

while(true){
    std::cout << name << " <~> " << "[RAM " << RAM_usage() << " || " << "CPU " << CPU_usage() << "] " << cwd << "\n";
    std::cout << "> ";
    getline(std::cin, command);
    system(command.c_str());
    }
}
