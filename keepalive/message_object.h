//
// Created by chenlehua on 2023/6/13.
//

#ifndef NETWORK_MESSAGE_OBJECT_H
#define NETWORK_MESSAGE_OBJECT_H

typedef struct {
    unsigned int type;
    char data[1024];
} messageObject;

#define  MSG_PING       1
#define  MSG_PONG       2
#define MSG_TYPE1       11
#define MSG_TYPE2       21

#endif //NETWORK_MESSAGE_OBJECT_H
