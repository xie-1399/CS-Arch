#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include "simulation.h"

void sigint_handler(int sig){
    std::cout<< "intereupt:" << sig <<std::endl;
}
void test_SIGINT(){
    signal(SIGINT,sigint_handler);
    printf("sleeping ~");
    sleep(60);
}
void test_SIGSEGV(){
    signal(SIGSEGV,sigint_handler);
    char *ptr = NULL;
    *ptr = 'a';  //wromng address
    exit(1);
}

const char* toc_str(){
    std::string str = "message";
    return str.c_str();
}

void exce(){
    int number1,number2;
    while(true){
        try {
            std::cin >> number1 >> number2;
            if(number1 != number2){
                throw std::runtime_error("not equal");
            }
            exit(EXIT_SUCCESS);
        }catch(std::runtime_error){
            std::cout << "try again" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}


int main(int argc, char** argv){
    //test_SIGINT();
    //test_SIGSEGV();
    //exce();

    // ./test --load-hex ./mm.hex, then get the command line value
    parseArgFirst(argc , argv);
    //setVerilatorseed(10);
    return 0;
}