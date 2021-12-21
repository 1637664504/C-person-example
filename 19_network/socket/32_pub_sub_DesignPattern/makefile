SERVER_OBJ=service.o topic_list_API.o
PUB_OBJ=pub.o
SUB_OBJ=sub.o

CFLAGS=-g -Wall

all: $(SERVER_OBJ) $(SUB_OBJ)
	$(CC) -o service.out		$(SERVER_OBJ) $(CFLAGS)
	#$(CC) -o pub.out		$(PUB_OBJ) $(CFLAGS)
	$(CC) -o sub.out		$(SUB_OBJ) $(CFLAGS)