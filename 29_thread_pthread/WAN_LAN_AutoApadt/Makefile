COMMON_OBJ = common/network/sys_link.o \
	common/sys/sys_thread.o

OBJ = $(COMMON_OBJ)  cycle_get_interface_address.o
CFLAGS = -g -lpthread -I inc

all: $(OBJ)
	$(CC) -o cycle_get_interface_address.out $^ $(CFLAGS)
