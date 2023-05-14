/*
 * 注意区分函数指针和返回指针类型的函数是不一样的
 * 函数指针可以作为返回值 / 可以当作函数参数 /甚至可以声明数组
 */
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>

typedef int (*funcptr)(int);
typedef void (*func)(int);

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

int square(int num){
    return num * num;
}

int compute(funcptr ptr,int num){
    return ptr(num);
}

int *arr(){
    int (*(arr2[])) ={
            (int []){0,1,2,3},
            (int []){4,5},
            (int []){6,7,8}
    };
    return  arr2;
}

char *getLine(void){
    const size_t sizeIncreasement = 10;
    char *buffer = (char *)malloc(sizeIncreasement);
    char *current = buffer;
    size_t max = sizeIncreasement;
    size_t length = 0;
    int character;
    if(current == NULL){
        return NULL;
    }
    while(1){
        character = fgetc(stdin);
        if(character =='\n'){
            break;
        }
        if(++length >=max){
            printf("over!");
            char *newBuffer = realloc(buffer,max += sizeIncreasement);
            if(newBuffer == NULL){
                free(buffer);
                return NULL;
            }
            current = newBuffer + (current - buffer);
            buffer == newBuffer;
        }
        *current++ = character;
    }
    *current = '\0';
    return buffer;
}

//different from int *arr[5]
void display2DArray(int (*arr)[5],int rows){
    for(int i= 0; i<rows; i++){
        for(int j=0; j<5; j++){
            printf("%d",arr[i][j]);
        }
    }
    printf("\n");
}



int main(){
    funcptr ptr = square;
    int number = compute(square,5);
    funcptr ptrs[128] = {NULL};

    // In fact it also can work
    func base;
    base = (funcptr) ptr;

    //copy string to char*
    char* buffer = malloc(strlen("  cat") + 1);
    strcpy(buffer,"  cat");

    int matrix[2][5] = {
            {1,2,3,4,5},
            {6,7,8,9,10}
    };
    display2DArray(matrix,2);

    printf("square value of 5 is %d\n",ptr(5));
    printf("square value of 5 is %d\n",number);
    getLine();
    return 0;
}