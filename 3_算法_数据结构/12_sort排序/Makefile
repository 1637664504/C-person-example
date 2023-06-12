CFLAGS:= -g -Wall
common_obj:= sort_array.o sortArray.o
test_obj:=sortArray_test.o

test: $(common_obj) $(test_obj)
	$(CC) -o sortArray_test.out $^ $(CFLAGS)

clean:
	rm *.o