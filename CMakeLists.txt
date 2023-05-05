cmake_minimum_required(VERSION 2.8)

project(RISCVZone)

add_executable(ProcessAPI OS/Introduce/ProcessAPI.cpp)
add_executable(Thread OS/Introduce/Thread.cpp)

add_executable(logisim OS/NJU/Example/logisim.c)
add_executable(hanoi-nr OS/NJU/Example/hanoi-nr.c)