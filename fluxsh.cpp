#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

std::string RAM_usage(){
    std::ifstream meminf("/proc/meminfo");
    std::string line;
    while(std::getline(meminf, line)){
        if(line.find("") == 0 || line.find("") == 0) return line;
    }
}

int main(){
    std::string command;
    std::string name = getenv("USER");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));


    std::cout << name << " <~> " << "[RAM 1.5GB || CPU 8%] " << cwd << "\n";
    std::cout << "> ";
    getline(std::cin, command);
    system(command.c_str());
}
