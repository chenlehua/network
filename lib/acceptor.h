//
// Created by parallels on 9/3/23.
//

#ifndef NETWORK_ACCEPTOR_H
#define NETWORK_ACCEPTOR_H

struct acceptor{
    int listen_port;
    int listen_fd;
} ;
struct acceptor *acceptor_init(int port);

#endif //NETWORK_ACCEPTOR_H
