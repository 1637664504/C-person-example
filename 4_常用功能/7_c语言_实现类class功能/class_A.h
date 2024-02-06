#pragma once
#ifndef __class_A_h__
#define __class_A_h__

typedef struct {
    int age;
    char name[32];
    int (*get_age)();
    char* (*get_name)();
}class_A;

int class_A_init(class_A* self, int age, char* name);
void class_A_destroy(class_A* self);
class_A* new_class_A(int age, char* name);
void free_class_A(class_A* self);

#endif