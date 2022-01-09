#include <stdio.h>
#include "sortArray.h"

int main(void)
{
    struct sortArray *array = NULL;

    sortArray_init(&array,16);

    array->add(array,9);
    array->add(array,1);
    array->add(array,5);
    array->add(array,3);
    array->add(array,7);
    array->show(array);

    array->del(array,9);
    array->del(array,3);
    array->del(array,1);
    array->show(array);
    
    sortArray_release(array);
    return 0;
}