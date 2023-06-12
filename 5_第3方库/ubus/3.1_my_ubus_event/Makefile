notify := ubus_pub.o ubus_pub_test.o
subscribe := ubus_sub.o ubus_sub_test.o
CFLAGS += -lubox -lubus -lblobmsg_json -Wall -g

default: $(notify) $(subscribe)
	$(CC) -o notify.out $(notify) $(CFLAGS)
	$(CC) -o subscribe.out $(subscribe) $(CFLAGS)

clean:
	rm *.o *.out