/*
 进程的系统调用的一些API，主要包括fork、exec、wait
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main(int argc,char *argv[]){
    printf("Hello World (pid:%d)\n",(int)getpid());
    int rc = fork();
    if(rc < 0 ){
        fprintf(stderr,"fork error");
        exit(1);
    } else if(rc == 0){
        printf("child pid %d\n",int(getpid()));
        char *myargs[3];
        myargs[0] = strdup("ls");
        myargs[1] = strdup("-al"); //File
        myargs[2] = NULL;
        execvp(myargs[0],myargs);   //run other
    } else{
        int wc = wait(NULL);  //Wait until the child finish
        printf("parent pid %d\n",int(getpid()));
    }
    return 0;
}

//fork：首先会复制对应的进程段，除了pid，同时会从复制的地方开始运行
//wait：等子进程运行结束
//exec: 会覆盖对应的代码段和数据段，而不是进行复制