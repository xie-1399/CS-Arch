#include <stdio.h>

int *swap(int *px , int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
    return px;
}

int main(int argc,char *argv[]){
    int i = 10 , j = 20; //0
    int *pi = &i;
    int *pc = pi; //指针之间可以进行相互的赋值
    //int *pd = 0; //Seg Fault
    printf("%d\n",*pi); //value
    printf("%d\n",pi); //address
    printf("%d\n",&i);
    printf("%d\n",&pi);
    int *p = swap(&i,&j);
    printf("i = %d , j = %d , *p = %d \n",i,j,*p);
    int a[10] = {0};
    printf("%d\n",a[2]);  // 2[a] also can work

    for(int  q = 0 ; argv[q] != NULL ; q++){
        printf("argv[%d] = %s\n",q,argv[q]);
    }
    return 0;
}
