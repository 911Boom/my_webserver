//
// Created by 着魔之人 on 24-7-2.
//

#include "Socket.h"


Socket::~Socket() {
    sockets::close(sockfd_);
}

void Socket::listen() const {
    sockets::listenSocket(sockfd_);
}

int Socket::accept(InetAddr* peeraddr) {
    struct sockaddr_in6 addr{};
    memZero(&addr, sizeof addr);
    int connfd = sockets::acceptSocket(sockfd_, &addr);
    if(connfd > 0) {
        peeraddr->setSockAddrInet6(addr);
    }
    return connfd;
}



void Socket::bindAddr(const InetAddr &localAddr) {
    sockets::bindAddrSocket(sockfd_, localAddr.getSockAddr());
}


