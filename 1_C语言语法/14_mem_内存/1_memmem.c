#include <stdio.h>
#include <string.h>

int main() {
    char haystack[16] = "Hello, world!";
    char needle[8] = "world";

    void * p = my_memmem(haystack, strlen(haystack), needle, strlen(needle));
    char str[16] = "123 search sdf";
    found  = my_memmem(str, strlen(str), "4445", 4);

    if (found) {
        printf("Found at position %p\n", &found);
        printf("%s\n", (char *)found);
    }
    else {
        printf("Not found\n");
    }

    return 0;
}