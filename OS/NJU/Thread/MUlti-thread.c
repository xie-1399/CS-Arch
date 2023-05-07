#include "thread.h"
#include <stdio.h>

/*
 * 这些线程被分配到不同的CPU上去执行
 * 线程之间是可以进行全局变量共享的
 */
void fn_a(){
    while(1){
        printf("fn_a");
    }
}

void fn_b(){
    while(1){
        printf("fn_b");
    }
}

static int x = 0;

void share(int id){
    usleep(id * 100000);
    printf("Hello from thread #%c\n","123456789ABCDEF"[x++]);
}

int main(){
    //create(fn_a);
    //create(fn_b);
    // Share the static id
    for(int i = 0 ; i < 10; i++){
        create(share);
    }
}