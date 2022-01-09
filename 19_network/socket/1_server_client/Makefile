
CFLAGS:=-g -Wall
array_obj:= lib/array/sort_array.o \
        lib/array/sortArray.o

common_obj:= $(array_obj) lib/common_sys.o

server_obj:=1_socket_server.o
client_obj:=2_socket_client.o

all: client server

client: $(client_obj)
	$(CC) -o 2_socket_client.out $^ $(CFLAGS)

server: $(common_obj) $(server_obj)
	$(CC) -o 1_socket_server.out $^ $(CFLAGS)

clean:
	rm *.o client server
