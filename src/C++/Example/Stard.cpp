#include <iostream>
#include "header.h"
/*
 * int Variable : bool int char long /long long/ (unsigned) /
 * float Variable : float double long double
 */

int main(){
    unsigned long long int num = 10;
    bool flag = true;
    float number = 1.2f;
    bool &ref = flag; //a refence，在类型后面
    ref = false;
    std::cout << flag << std::endl;
    std::cout << sizeof (bool ) << std::endl;
    std::cout << "Hello World!" << std::endl;
    std::cin.get(); //in fact , just read one (like getchar)

    initial();
    int value = 10;
    useref(value);
    std::cout << "value:" << value << std::endl;
}