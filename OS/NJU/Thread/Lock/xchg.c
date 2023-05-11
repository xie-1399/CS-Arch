/*
 * 使用原子指令来实现自旋锁
 */

//根据标记进行判断
#include "../thread.h"

#define N 100000000

int cas(int *addr,int cmp_val,int new_val){
    int old_val = *addr;
    if(old_val == cmp_val){
        *addr =  new_val;
        return 0;
    } else{
        return 1;
    }
}
long sum = 0;

void Tsum() {
    for (int i = 0; i < N; i++) {
        asm volatile("lock addq $1, %0": "+m"(sum));
    }
}

int main() {
    create(Tsum);
    create(Tsum);
    join();
    printf("sum = %ld\n", sum);
}