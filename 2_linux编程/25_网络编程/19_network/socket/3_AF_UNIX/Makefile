CFLAGS:= -g -Wall -pthread

common_obj:= lib/common.o \
		lib/client_info.o

server_obj:= 1_AF_UNIX_server.o
PKG_SERVER:= server

client_obj:= 2_AF_UNIX_client.o
PKG_CLIENT:= client

all: server client

server: $(common_obj) $(server_obj)
	$(CC) -o $(PKG_SERVER) $^ $(CFLAGS)

client: $(client_obj)
	$(CC) -o $(PKG_CLIENT) $^ $(CFLAGS)