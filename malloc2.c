#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studentTag {
    char name[10];
    int age;
    double gpa;
} student;                    


int main(void) {
    student *s = (student *) malloc(sizeof(student));
    if (s == NULL) {
        fprintf(stderr, "힙 메모리가 부족하므로 할당 불가\n");
        exit(1);
    }
    
    strcpy(s->name, "Lee");
    (*s).age = 25; 

    printf("이름: %s, 나이: %d", s->name, s->age);

    free(s);
    return 0;
}