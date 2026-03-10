cmake_minimum_required(VERSION 3.10)
project(fluxsh)

set(CMAKE_CXX_STANDARD 17)

add_executable(fluxsh
    fluxsh.cpp
    system_monitor/system_monitor.cpp
)

target_include_directories(fluxsh PUBLIC system_monitor)
