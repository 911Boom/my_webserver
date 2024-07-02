//
// Created by 着魔之人 on 24-6-22.
//

#ifndef MY_WEBSERVER_INETADDR_H
#define MY_WEBSERVER_INETADDR_H

#include <netinet/in.h>
#include "base/StringPiece.h"
#include "server/SockerOps.h"


class InetAddr {
public:
    InetAddr(StringArg ip, uint16_t port, bool ipv6 = false);

    explicit InetAddr(const struct sockaddr_in &addr) : addr_(addr) {}

    explicit InetAddr(const struct sockaddr_in6 &addr6) : addr6_(addr6) {}

    [[nodiscard]] sa_family_t family() const { return addr_.sin_family; }

    [[nodiscard]] string toIp() const;

    [[nodiscard]] string toIpPort() const;

    [[nodiscard]] uint16_t port() const;

    [[nodiscard]] const struct sockaddr *getSockAddr() const {
        return sockets::sockaddr_cast(&addr6_);
    }

    void setSockAddrInet6(const struct sockaddr_in6 &addr6) { addr6_ = addr6; }

    [[nodiscard]] uint32_t ipv4NetEndian() const;

    [[nodiscard]] uint16_t portNetEndian() const { return addr_.sin_port; }

    static bool HostNameToInetAddr(StringArg hostname, InetAddr *result);

private:
    union {
        struct sockaddr_in addr_{};
        struct sockaddr_in6 addr6_;
    };
};


#endif //MY_WEBSERVER_INETADDR_H
