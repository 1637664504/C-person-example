SERVER_OBJ= topic_list_API.o service.o
PUB_OBJ=pub.o
SUB_OBJ=sub.o
CFLAGS=-g -Wall

all: $(SERVER_OBJ) $(SUB_OBJ) $(PUB_OBJ)
	$(CC) -o service.out		$(SERVER_OBJ) $(CFLAGS)
	$(CC) -o pub.out		$(PUB_OBJ) $(CFLAGS)
	$(CC) -o sub.out		$(SUB_OBJ) $(CFLAGS)

%.o:%.c
	$(CC) -c $^ $(CFLAGS)
