COMMON_OBJ = common/network/sys_link.o \
	common/sys/sys_thread.o

OBJ = $(COMMON_OBJ)  cycle_get_interface_address.o
CFLAGS = -g -lpthread -I inc

LAN_OBJ = listen_interface_packs.o 
lan: $(LAN_OBJ) $(COMMON_OBJ)
	$(CC) -o listen_interface_packs.out $^ $(CFLAGS)

all: $(OBJ)
	$(CC) -o cycle_get_interface_address.out $^ $(CFLAGS)
