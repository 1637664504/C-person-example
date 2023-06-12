#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <assert.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>


static void signal_cb(int fd,short events,void *arg)
{
	printf("sigint trigger\n");
}

int main()
{
    struct event_base * base = event_init();
    assert( base != NULL );

    struct event* signal_event = evsignal_new(base,SIGINT,signal_cb,base);
    event_add(signal_event,NULL);

    event_base_dispatch(base);
    event_free(signal_event);
    event_base_free(base);
}


