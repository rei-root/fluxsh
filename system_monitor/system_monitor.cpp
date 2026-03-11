#include "system_monitor.hpp"
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <thread>
#include <chrono>

std::string RAM_usage(){
    std::ifstream meminf("/proc/meminfo");
    std::string line;
    long total = 0, available = 0;
    if(!meminf.is_open()){
        throw std::runtime_error("Error: can't open meminfo");
    }
    while (std::getline(meminf, line)) {
        if (line.find("MemTotal:") == 0){
            sscanf(line.c_str(), "MemTotal: %ld", &total);
        }
        if (line.find("MemAvailable: ") == 0){
            sscanf(line.c_str(), "MemAvailable: %ld", &available);
        }
    }

    if(total == 0){return "0/0kb";}

    long RAM_usage_Kb = total - available;

    double RAM_usage_Gb = RAM_usage_Kb / 1024.0 / 1024.0;

    return std::to_string(RAM_usage_Gb).substr(0, 4) + "Gb";
}

std::pair<long, long> read_stat() {
    std::ifstream cpuinf("/proc/stat");
    std::string line;
    long user = 0, nice = 0, system = 0, idle = 0, iowait = 0, irq = 0, softirq = 0, steal = 0, guest = 0, guest_nice = 0;
    if(!cpuinf.is_open()){
        throw std::runtime_error("Error: can't open cpuinfo");
    }

    std::getline(cpuinf, line);
        if(line.find("cpu ") == 0){
            sscanf(line.c_str(), "cpu %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
        }

    long total = user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice;
    long idle_ = idle + iowait;
    return {total, idle_};
}

std::string CPU_usage(){
    //Высчитываем первый тик
    auto [total_1, idle_1] = read_stat();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    //Высчитываем второй тик
    auto [total_2, idle_2] = read_stat();

    //Высчитываем разницу
    long total_delta = total_2 - total_1;
    long idle_delta = idle_2 - idle_1;

    if(total_delta == 0){
        return "0.00%";
    }

    //Высчитываем использование CPU
    double cpu_usage = ((double)total_delta - idle_delta) / total_delta * 100;

    return std::to_string(cpu_usage).substr(0, 4) + "%";
}
