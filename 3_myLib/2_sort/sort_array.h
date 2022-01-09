#ifndef _sort_array_h_
#define _sort_array_h_
enum array_move_direct{
    ARRAY_LEFT_MOVE = 0,
    ARRAY_RIGHT_MOVE
};

void array_move_right(int a[],int len);
void array_move_left(int a[],int len);
void array_move(int a[],int len,enum array_move_direct direct);
int array_insert_sort(int a[], unsigned int len, int number);
int array_del_sort(int a[], unsigned int len, int number);
void array_dump(int a[],int len);

#endif