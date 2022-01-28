INCLUDE_FLAGS=-I ../lib
#LIB_FLAGS=-L ../lib
CFLAGS:=-Wall -g -lpthread $(INCLUDE_FLAGS)
OBJ:=thread_manage_test.o ../lib/sys_thread.o

all: $(OBJ)
	$(CC) -o thread_manage_test.out $^ $(CFLAGS)
