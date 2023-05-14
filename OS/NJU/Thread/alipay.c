#include "thread.h"

unsigned long balance = 100;
/*
 * while true; do ./demo ;done;
 */
void Alipay_withdraw(int amt) {
  if (balance >= amt) {
    usleep(1); // unexpected delays
    balance -= amt;
  }
}

int func(int c){
    int i=10;
    int a = i;
    int b = i;
    return a+b+c;
}
void Talipay(int id) {
  Alipay_withdraw(100);
}

int main() {
  create(Talipay);
  create(Talipay);
  join();
  printf("balance = %lu\n", balance);

}




