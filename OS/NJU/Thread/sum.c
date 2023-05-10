#include "thread.h"
/*
 * 虽然是简单的一些加法，但是由于原子性会带来一些问题
 * 但是如果出现编译器优化时，出现的结果会不一样
 * gcc sum.c -O1 -o demo -lpthread
 * gcc sum.c -O2 -o demo -lpthread
 */
#define N 100000000
#define UNLOCK 0
#define LOCK 1
void failtry();
long sum = 0;
int locked = UNLOCK;

void Tsum() {
  for (int i = 0; i < N; i++) {
    sum++;
  }
}

int main() {
  create(Tsum);
  create(Tsum);
  join();
  printf("sum = %ld\n", sum);

  failtry();
}

void failtry(){
    /*
     * not work!
     */
retry:
    if(locked != UNLOCK){
        goto retry;
    }
    locked = LOCK;
    sum ++;
    locked = UNLOCK;
}