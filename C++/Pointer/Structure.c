#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _person{
    int age;
    char *firstName;
}Person;

void initial(){
    const char *header = "sound";
    char header_array[] = "sound";
    char head_str[13];
    strcpy(head_str,"spund");
    // On the Heap and sometimes char equals int
    char *header_copy = (char *)malloc(strlen("sound") + 1);
    strcpy(header_copy,"sound");

    //just copy the address
    char *HeaderTable[4] = {NULL};
    HeaderTable[0] = "str1";
    HeaderTable[1] = HeaderTable[0];
}

int compare(){
    char *comp = "Quit";
    char temp[10];
    scanf("%s",temp);
    /*
     * Wrong Way
    if(temp == comp){
     ...
    }
    */
    return strcmp(comp,temp);
}

void useStructure(){
    Person person;
    person.age =23;
    person.firstName = "xxl";
    // Use Pointer
    Person *pointer_person;
    pointer_person -> age = 23;
    pointer_person ->firstName = "xxl";
}

int main(int argc, char **argv){
    // show how to use command line(to main)
    for (int i = 0 ; i<argc ; i++){
        printf("argv[%d] : %s\n",i,argv[i]);
    }
    return 0;
}
