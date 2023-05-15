#include <getopt.h>
#include "simulation.h"
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>

static const struct option long_options[] =
        {
                {"help", no_argument, 0, 1},
                {"load-hex", required_argument, 0, 2},
                {"load-elf", required_argument, 0, 3},
                {"load-bin", required_argument, 0, 4},
                {0,0,0,0}
        };

void parseArgFirst(int argc, char** argv){
    char *str = NULL;
    int index = -1;
    int command = getopt_long(argc,argv,"abc:d",long_options,&index);
    if(command == -1)exit(EXIT_FAILURE);
    switch (command) {
        case 2:{
            str = optarg;
            std::cout<<"option value:" << str<<std::endl;
            std::cout<<"index value:" << index <<std::endl;
        }
        default:
            printf("default");
    }
    exit(EXIT_SUCCESS);
}

int mkpath(std::string s,mode_t mode){
    size_t pos=0;
    std::string dir;
    int mdret;

    if(s[s.size()-1]!='/'){
        // force trailing / so we can handle everything in loop
        s+='/';
    }

    while((pos=s.find_first_of('/',pos))!=std::string::npos){
        dir=s.substr(0,pos++);
        if(dir.size()==0) continue; // if leading / first time is 0 length
        if((mdret=mkdir(dir.c_str(),mode)) && errno!=EEXIST){
            return mdret;
        }
    }
    return mdret;
}