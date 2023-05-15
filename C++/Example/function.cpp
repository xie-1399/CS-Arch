#include "header.h"
#include <iostream>
//void log(const char* message);  // just declare

/*
 * how to use head file with cpp :
 * 在头文件中声明函数，在实际的cpp中去写这个函数，这样include的时候就能需要进行调用
 * 在一个cpp里面定义函数，看起来是比较好的风格
 */

void initial(){
    log("string\n");
}

void log(const char* message){
    std::cout << message << std::endl;
}

void useref(int& value){
    value++;
}

