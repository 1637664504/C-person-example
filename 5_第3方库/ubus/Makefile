notify := 2_ubus_notifier.o
subscribe := 2.1_ubus_subscribe.o
CFLAGS += -Wall -g -lubox -lubus

default: $(notify) $(subscribe)
	$(CC) -o notify.out $(notify) $(CFLAGS)
	$(CC) -o subscribe.out $(subscribe) $(CFLAGS)

clean:
	rm *.o *.out