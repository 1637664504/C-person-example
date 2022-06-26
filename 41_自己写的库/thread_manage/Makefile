obj:= sys_thread.o
targetLib:=libsys_thread.so
#ShareLibFlags:=-shared -fPIC
CFLAGS := -shared -fPIC

#Debug
CFLAGS += -ggdb3 -o0

default: $(obj)
	$(CC) -o $(targetLib) $(obj) $(CFLAGS)

testObj=test.o
test: $(testObj)
	$(CC) -o $^ $(testObj) $(CFLAGS) -lsys_thread


clean:
	rm -rf *.so *.o
