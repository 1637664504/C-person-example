#include <string.h>
#include <stdlib.h>
#include "class_A.h"

static int _get_age(class_A* self) {
    return self->age;
};

static char* _get_name(class_A* self) {
    return self->name;
};

int class_A_init(class_A* self, int age, char* name)
{
    self->age = age;
    memcpy(self->name, name, sizeof(self->name) - 1);
    self->get_age = _get_age;
    self->get_name = _get_name;

    return 0;
}

void class_A_destroy(class_A* self)
{

}

class_A* new_class_A(int age, char* name)
{
    class_A* p = malloc(sizeof(class_A));
    if (p == NULL)
        return NULL;

    class_A_init(p, age, name);
    return p;
}

void free_class_A(class_A* self)
{
    class_A_destroy(self);
    free(self);
    self = NULL;
}
