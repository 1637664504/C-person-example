notify := 2_ubus_event_one_func_server.o
subscribe := 2_ubus_event_one_func_client.o
CFLAGS += -lubox -lubus -lblobmsg_json -Wall -g

default: $(notify) $(subscribe)
	$(CC) -o notify.out $(notify) $(CFLAGS)
	$(CC) -o subscribe.out $(subscribe) $(CFLAGS)

clean:
	rm *.o *.out