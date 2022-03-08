
CFLAGS:= -Wall
GenDynmaicLibFLAGS := -fPIC -shared
common:= list.o

all: lib test


lib: $(common)
	$(CC) -o liblist.so $^ $(GenDynmaicLibFLAGS)

test:
	$(CC) test_list.c list.o -o test_list
	$(CC) test_list_add_tail.c list.o -o test_list_add_tail
