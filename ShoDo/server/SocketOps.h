//
// Created by 着魔之人 on 24-6-26.
//

#ifndef MY_WEBSERVER_SOCKETOPS_H
#define MY_WEBSERVER_SOCKETOPS_H

#include <arpa/inet.h>
#include <cassert>
#include <unistd.h>
#include "base/types.h"

namespace sockets {


    const struct sockaddr *sockaddr_cast(const struct sockaddr_in6 *addr) {
        return static_cast<const struct sockaddr *>(implicit_cast<const void *>(addr));
    }

    struct sockaddr *sockaddr_cast(struct sockaddr_in6 *addr) {
        return static_cast<struct sockaddr *>(implicit_cast<void *>(addr));
    }

    const struct sockaddr *sockaddr_cast(const struct sockaddr_in *addr) {
        return static_cast<const struct sockaddr *>(implicit_cast<const void *>(addr));
    }

    struct sockaddr *sockaddr_cast(struct sockaddr_in *addr) {
        return static_cast<struct sockaddr *>(implicit_cast<void *>(addr));
    }

    const struct sockaddr_in *sockaddr_in_cast(const struct sockaddr *addr) {
        return static_cast<const struct sockaddr_in *>(implicit_cast<const void *>(addr));
    }

    const struct sockaddr_in6 *sockaddr_in6_cast(const struct sockaddr *addr) {
        return static_cast<const struct sockaddr_in6 *>(implicit_cast<const void *>(addr));
    }




    void fromIpPort(const char *ip, uint16_t port, struct sockaddr_in *addr) {
        // 用Ip和Port构造addr6
        addr->sin_family = AF_INET;
        addr->sin_port = htobe16(port);
        if (::inet_pton(AF_INET, ip, &addr->sin_addr) <= 0) {
            // LOG_ERR << "SockerOops_fromIpPort";
        }
    }

    void fromIpPort(const char *ip, uint16_t port, struct sockaddr_in6 *addr) {
        // 用Ip和Port构造addr4
        addr->sin6_family = AF_INET6;
        addr->sin6_port = htobe16(port);
        if (::inet_pton(AF_INET6, ip, &addr->sin6_addr) <= 0) {
            // LOG_ERR << "SockerOops_fromIpPort";
        }
    }

    void toIp(char *buf, size_t size, const struct sockaddr *addr) {
        if (addr->sa_family == AF_INET) {
            assert(size >= INET_ADDRSTRLEN);
            const struct sockaddr_in *addr4 = sockaddr_in_cast(addr);
            ::inet_ntop(AF_INET, &addr4->sin_addr, buf, static_cast<socklen_t>(size));
        } else if (addr->sa_family == AF_INET6) {
            assert(size >= INET6_ADDRSTRLEN);
            const struct sockaddr_in6 *addr6 = sockaddr_in6_cast(addr);
            ::inet_ntop(AF_INET6, &addr6->sin6_addr, buf, static_cast<socklen_t>(size));
        }
    }


    void toIpPort(char *buf, size_t size, const struct sockaddr *addr) {
        if (addr->sa_family == AF_INET) {
            toIp(buf, size, addr);
            size_t end = ::strlen(buf);
            const struct sockaddr_in *addr4 = sockaddr_in_cast(addr);
            uint16_t port = be16toh(addr4->sin_port);
            assert(size > end);
            snprintf(buf + end, size - end, ":%u", port);

        } else if (addr->sa_family == AF_INET6) {
            buf[0] = '[';
            toIp(buf + 1, size - 1, addr);
            size_t end = ::strlen(buf);
            const struct sockaddr_in6 *addr6 = sockaddr_in6_cast(addr);
            uint16_t port = be16toh(addr6->sin6_port);
            assert(size > end);
            snprintf(buf + end, size - end, "]:%u", port);
        }
    }
    void close(int sockfd)
    {
        if (::close(sockfd) < 0) {
//        LOG_SYSERR << "sockets::close";
        }
    }
    void bindAddrSocket(int sockfd, const struct sockaddr *addr) {
        // 连接 Addr 与 Socket 连接失败放弃
        int ret = ::bind(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
        if (ret < 0) {
//            LOG_SYSFATAL << "sockets::bindAddrSocked";";
        }
    }

    void listenSocket(int sockfd) {
        // 监听 Socket 监听失败则放弃
        int ret = ::listen(sockfd, SOMAXCONN);
        if (ret < 0) {
//            LOG_SYSFATAL << "sockets::listenSocked";
        }
    }

    int acceptSocket(int sockfd,struct sockaddr_in6 *addr) {
        auto addrlen = static_cast<socklen_t>(sizeof *addr);
        int connfd = ::accept(sockfd, sockaddr_cast(addr), &addrlen);
        if(connfd < 0 ) {
            // LOG_FATAL << "sockets::acceptSocket"
        }
        return connfd;
    }
}


#endif //MY_WEBSERVER_SOCKETOPS_H
