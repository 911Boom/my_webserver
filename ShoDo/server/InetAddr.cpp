//
// Created by 着魔之人 on 24-6-22.
//

#include "server/InetAddr.h"
#include <netdb.h>
#include <netinet/in.h>


InetAddr::InetAddr(StringArg ip, uint16_t port, bool ipv6) {
    if (ipv6 || strchr(basename(ip.c_str()), ':')) {
        memZero(&addr_, sizeof addr_);
        sockets::fromIpPort(ip.c_str(),port,&addr6_);
    } else {
        memZero(&addr_, sizeof addr_);
        sockets::fromIpPort(ip.c_str(),port,&addr_);
    }
}

string InetAddr::toIp() const {
    char buf[64] = "";
    sockets::toIp(buf, sizeof buf,getSockAddr());
    return buf;
}

string InetAddr::toIpPort() const {
    char buf[64] = "";
    sockets::toIpPort(buf, sizeof buf,getSockAddr());
    return buf;
}

uint16_t InetAddr::port() const {
    return be16toh(portNetEndian());
}

uint32_t InetAddr::ipv4NetEndian() const {
    assert(family() == AF_INET);
    return addr_.sin_addr.s_addr;
}

static __thread char t_resolveBuffer[64 * 1024];

bool InetAddr::HostNameToInetAddr(StringArg hostname, InetAddr* out) {
    //解析hostname to IneAddr
    assert(out != nullptr);
    struct hostent host_{};
    struct hostent* result = nullptr;
    int h_errnop = 0;
    memZero(&host_, sizeof(host_));
    int ret = gethostbyname_r(hostname.c_str(), &host_, t_resolveBuffer,sizeof t_resolveBuffer, &result, &h_errnop);
    if(ret == 0 && result != nullptr) {
        assert(result->h_addrtype == AF_INET&&result->h_length == sizeof(uint32_t));
        out->addr_.sin_addr = *reinterpret_cast<struct in_addr*>(result->h_addr);
        return true;
    } else {
        if (ret) {
//            LOG_SYSER << "HostNameToInetAddr;
        }
        return false;
    }
}


