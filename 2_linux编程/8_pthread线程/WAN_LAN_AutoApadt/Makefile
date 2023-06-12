COMMON_OBJ = common/network/sys_link.o \
	common/sys/sys_thread.o

CFLAGS = -g -lpthread -I inc -Wall

LAN_OBJ = lan_listen_interface_dhcp.o
WAN_OBJ = wan_get_interface_ip.o
MAIN_OBJ = monitor_interface_netlink.o  $(WAN_OBJ) $(LAN_OBJ) $(COMMON_OBJ)

lan: $(LAN_OBJ) $(COMMON_OBJ)
	$(CC) -o listen_interface_packs.out $^ $(CFLAGS) -DDEBUG

wan: $(WAN_OBJ) $(COMMON_OBJ)
	$(CC) -o monitor_interface_netlink.out $^ $(CFLAGS) -DDEBUG

all: $(MAIN_OBJ)
	$(CC) -o monitor_interface_netlink.out $^ $(CFLAGS)
