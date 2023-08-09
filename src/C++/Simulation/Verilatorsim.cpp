#include <verilated.h>
#include "simulation.h"
#include <iostream>

void setVerilatorseed(int value){
    Verilated::randSeed(value);
    std::cout << value << std::endl;
}