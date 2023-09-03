//
// Created by parallels on 9/3/23.
//

#ifndef NETWORK_EVENT_DISPATCHER_H
#define NETWORK_EVENT_DISPATCHER_H
#include "channel.h"
#include "event_loop.h"

struct event_dispatcher{
    const char *name;

    void *(*init)(struct  event_loop *eventLoop);
    int (*add)(struct event_loop * eventLoop, struct channel * channel);
    int (*del)(struct event_loop * eventLoop, struct channel * channel);
    int (*update)(struct event_loop * eventLoop, struct channel * channel);
    int (*dispatch)(struct event_loop * eventLoop, struct timeval *);
    void (*clear)(struct event_loop * eventLoop);

};



#endif //NETWORK_EVENT_DISPATCHER_H
