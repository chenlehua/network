//
// Created by parallels on 9/3/23.
//

#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H
#include "event_loop.h"

int isInSameThread(struct event_loop *eventLoop);
void assertInSameThread(struct event_loop *eventLoop);


#endif //NETWORK_UTILS_H
