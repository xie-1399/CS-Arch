/*
 * C语言所有的与输入输出相关的函数
 * 文件处理
 */

#include <stdio.h>
#include <stdlib.h>

void Readline(char *path){
    char *filename = path;
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp == NULL){
        perror(path);
        exit(EXIT_FAILURE);
    }
    char buffer[100];
    while(fgets(buffer, 100, fp) != NULL) {
        printf("%s", buffer);
    }
    fclose(fp);
}

void ReadFile(char *path, int usegets){
    char *filename = path;
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp == NULL){
        perror(path);
        exit(EXIT_FAILURE);
    }
    int ch = getc(fp);
    char str[100];
    while (ch != EOF){
        printf("%c",ch);
        if(usegets){
            ch = getc(fp); //Or fgetc
        } else{
            fgets(str,sizeof (str),fp);
            printf("line: %s\n",str);
            fclose(fp);
            exit(EXIT_SUCCESS);
        }
    }
    printf("End ! \n");
    fclose(fp);
}

void writefile(char *path , int line){
    char *filename = path;
    FILE *fp;
    if(line){
        fp = fopen(filename,"a");
    } else{
        fp = fopen(filename,"w"); // a 追加
    }
    if(fp == NULL){
        perror(path);
        exit(EXIT_FAILURE);
    }
    char str[100];
    if(line){
        fgets(str,100,stdin);
        fputs(str,fp);
    } else{
        int ch = getchar();
        fputc(ch,fp);
    }
    fclose(fp);
}

void Read(){
    /*
     * just for stdin and stdout : getchar gets scanf
     * for all stream : fgetc getc , fgets ,fscanf
     * getchar : 用于从控制台或文件中读取一个字符，并将其作为函数的返回值返回
     * gets : 从标准输入中读取一行字符，但已被废弃
     * fgets(char *str, int n, FILE *stream)
     * getc : 用于从文件中读取一个字符，并将其作为函数的返回值返回,getc可用于任何流
     * fgetc：
     */
    int ch;
    ch =getchar();
    printf("%c\n",ch);

    char str[100];
    fgets(str,100,stdin);
    printf("%s\n",str);

    ch = getc(stdin);
    printf("%c\n",ch);

    ReadFile("./funcPointer.c",0);
    Readline("./funcPointer.c");
}

void usefflush(){
    printf("Hello\n");
    fflush(stdout);
    printf("world\n");
    exit(EXIT_SUCCESS);
}

void Write(){
    /*
     * putchar/puts/printf -- for stdout
     * fputc putc / fputs / fprintf
     */
    int ch = getchar();
    putchar(ch);

    char str[100];
    fgets(str, 100 , stdin);
    puts(str);

    writefile("./test.txt",0);
    writefile("./test.txt",1);
}

int main(){
    Read();
    Write();
    usefflush();
    return 0;
}