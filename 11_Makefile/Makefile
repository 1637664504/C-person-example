OBJ:=main.o add.o
CFLAGS:=-g
demo: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $^

clean:
	rm *.o demo -rf

