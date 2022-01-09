OBJ:=multi_wan_set_route.o
CFLGAS:= -g -pthread -Wall
#TARGET_OBJ:=a.out
TARGET_OBJ:=a.out

all: $(OBJ)
	$(CC) -o $(TARGET_OBJ) $^ $(CFLGAS)

%.o: %.c
	$(CC) -c $^ $(CFLGAS)