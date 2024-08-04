//
// Created by 着魔之人 on 24-7-2.
//

#ifndef MY_WEBSERVER_SOCKET_H
#define MY_WEBSERVER_SOCKET_H

#include "server/InetAddr.h"
#include "server/SocketOps.h"

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <cstdio>

class Socket {
private:
    const int sockfd_;

public:
    explicit Socket(int sockfd): sockfd_(sockfd) {}
    ~Socket();
    [[nodiscard]] int getFd() const { return sockfd_; };
    void listen() const;
    int accept(InetAddr* peeraddr);
    void bindAddr(const InetAddr& localaddr);
};


#endif //MY_WEBSERVER_SOCKET_H
