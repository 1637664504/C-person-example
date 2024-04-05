#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

int main ( int argc, char *argv[] )
{
    if ( argc != 2 )
    {
        fprintf( stderr, "Usage: %s [file]\n", argv[0] );
        exit( EXIT_FAILURE );
    }

    char *file = argv[1];
    FILE* fp = fopen(file, "w");
    if (fp == NULL) {
        perror("open file failed");
        return 0;
    }

    char buf[1024];
    uint32_t len = 0;
    while (len = read(STDIN_FILENO, buf, sizeof(buf))) {
        fwrite(buf, 1, len, stdout);
        fwrite(buf, 1, len, fp);
    }
    fclose(fp);

    return 0;
}