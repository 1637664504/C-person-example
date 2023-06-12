#ifndef _sortArray_h_
#define _sortArray_h_

struct sortArray{
    unsigned int MaxNumber;
    unsigned int count;
    int (*add)(struct sortArray *a, int number);
    int (*del)(struct sortArray *a, int number);
    void (*show)(struct sortArray *a);
    int array[0];
};
int sortArray_init(struct sortArray **a, int number);
void sortArray_release(struct sortArray *a);

#endif