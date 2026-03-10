#include "system_monitor.hpp"
#include <fstream>


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
        if( line.find("MemAvailable: ") == 0){
            sscanf(line.c_str(), "MemAvailable: %ld", &available);
        }
    }

    if(total == 0){return "0/0kb";}

    long RAM_usage_Kb = total - available;

    double RAM_usage_Gb = RAM_usage_Kb / 1024.0 / 1024.0;

    return std::to_string(RAM_usage_Gb).substr(0, 4) + "Gb";
}
