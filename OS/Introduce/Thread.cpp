// Os Thread
#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;
/*
 * g++ -o Thread Thread.cpp -pthread
 */

static int counter = 0;

void *mythread(void *args){
    cout<< (char*)args << endl;
    for(int i = 0; i<1e4 ; i++){
        counter ++;
    }
    return NULL;

}

int main(int argc , char *argv[]){
    pthread_t p1,p2;
    int rc;
    cout<< "Start" << endl;
    rc = pthread_create(&p1, NULL, mythread, (void *) "A");
    assert(rc==0);
    rc = pthread_create(&p2, NULL, mythread, (void *) "B");
    assert(rc==0);

    //join,等待线程完成
    rc = pthread_join(p1,NULL);
    assert(rc == 0);
    rc = pthread_join(p2,NULL);
    assert(rc == 0);
    cout << "End"<<endl;
    cout << "Counter：" << counter << endl;
    return 0;

}
