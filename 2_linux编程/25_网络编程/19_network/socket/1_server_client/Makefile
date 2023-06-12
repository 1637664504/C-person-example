
CFLAGS:=-g -Wall
array_obj:= lib/array/sort_array.o \
        lib/array/sortArray.o

common_obj:= $(array_obj) lib/common_sys.o

server_obj:=1_socket_server.o
client_obj:=2_socket_client.o

all: client server unxi_client unix_server

client: $(client_obj)
	$(CC) -o 2_socket_client.out $^ $(CFLAGS)

server: $(common_obj) $(server_obj)
	$(CC) -o 1_socket_server.out $^ $(CFLAGS)

unxi_client: 4_AF_UNIX_socket_client.o
	$(CC) -o 4_AF_UNIX_socket_client.out $^ $(CFLAGS)

unix_server: $(common_obj) 3_AF_UNXI_socket_server.o
	$(CC) -o 3_AF_UNXI_socket_server.out $^ $(CFLAGS)

clean:
	rm *.o *.out
