#include<stdio.h>
#include <string.h>

struct student 
{
    int id;
    char name[20];
    float percentage;
};

typedef struct mStruct {
    char* stringy;
} myStruct;

myStruct * structObj;

void doSomething(char* stringy)
{
    structObj->stringy = stringy;
}

int main(int argc, char** argv)
{
    char* a = "abc\n";
    structObj = malloc(sizeof(myStruct));
    doSomething(a);
    a = "qxr\n";
    printf("%s%s", a, structObj->stringy);

    struct student record = {0}; //Initializing to null
    record.id=1;
    strcpy(record.name, "Phil");
    record.percentage = 86.5;

    printf("Id is: %d \n", record.id);
    printf("Name is: %s \n", record.name);
    printf("Percentage is: %f \n", record.percentage);
    return 0;
}