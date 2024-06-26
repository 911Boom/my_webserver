//
// Created by 着魔之人 on 24-6-22.
//

#include "InetAddr.h"
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>




InetAddr::InetAddr(StringArg ip, uint16_t port, bool ipv6) {
    if(ipv6 || strchr(basename(ip.c_str()),':')) {
        memZero(&addr_, sizeof addr_);

    }
    addr_.sin_port = htons(ip.c_str());
}

string InetAddr::toIp() const {
    char buf[64] = "";

    return {};
}

string InetAddr::toIpPort() const {
    return {};
}

uint16_t InetAddr::port() const {
    return 0;
}

uint32_t InetAddr::ipv4NetEndian() const {
    return 0;
}

bool InetAddr::resolve(StringArg hostname, InetAddr *result) {
    return false;
}


