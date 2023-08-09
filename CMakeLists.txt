cmake_minimum_required(VERSION 2.9)

project(CSArch)

add_executable(ProcessAPI OS/Introduce/ProcessAPI.cpp)
add_executable(Thread OS/Introduce/Thread.cpp)
add_executable(logisim OS/NJU/Example/logisim.c)
add_executable(hanoi-nr OS/NJU/Example/hanoi-nr.c)

# About Thread
add_executable(MUlti-thread OS/NJU/Thread/MUlti-thread.c)
add_executable(stack-probe OS/NJU/Thread/stack-probe.c)
add_executable(alipay OS/NJU/Thread/alipay.c)
add_executable(sum OS/NJU/Thread/sum.c)
add_executable(mem-ordering OS/NJU/Thread/mem-ordering.c)
add_executable(peterson-barrier OS/NJU/Thread/peterson-barrier.c)

#About Lock
add_executable(xchg OS/NJU/Thread/Lock/xchg.c)

#About C++
add_executable(funcPointer src/C++/Pointer/funcPointer.c)
add_executable(Structure srcC++/Pointer/Structure.c)
add_executable(IO src/C++/Pointer/IO.c)
add_executable(Stard src/C++/Example/function.cpp C++/Example/Stard.cpp)
add_executable(signal src/C++/Simulation/signal_function.cpp
        src/C++/Simulation/parseArgFirst.cpp src/C++/Simulation/Verilatorsim.cpp)