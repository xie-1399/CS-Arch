#include <stdio.h>
#include <stdarg.h>

/*
 * 静态局部变量 ： 在第一次函数被调用时创造并初始化，但在函数退出时它不死亡，而是保持其值等待函数下一次被调用。
 * 全局变量：普通全局变量可以在各个文件中使 用，可以在项目内别的.c文件中被看到，所以要确保不能重名
 * 静态全局变量 ： 静态全局变量定义时在定义前加static关键字， 告诉编译器这个变量只在当前本文件内使用，在别的文件中绝对不会使用。
 */


int *swap(int *px , int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
    return px;
}

void get_char_while(){
    char ch;
    while ((ch = getchar())!=EOF && ch != '\n'){
        printf("%c\n",ch);
    }
}

/*
 * 可变的函数参数列表,但是好像顺序不太对的颜值高i
 */
double average(int num,...)
{

    va_list valist;
    double sum = 0.0;
    int i;

    /* 为 num 个参数初始化 valist */
    va_start(valist, num);
    /* 访问所有赋给 valist 的参数 */
    for (i = 0; i < num; i++)
    {
        printf("number : %d\n",va_arg(valist,int));
        sum += va_arg(valist, int);
    }
    /* 清理为 valist 保留的内存 */
    va_end(valist);
    return sum/num;
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

//    for(int  q = 0 ; argv[q] != NULL ; q++){
//        printf("argv[%d] = %s\n",q,argv[q]);
//    }
    //get_char_while();
    average(3,1,2,3);
    return 0;
}