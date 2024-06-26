//
// Created by 着魔之人 on 24-6-26.
//

#ifndef MY_WEBSERVER_SOCKEROPS_H
#define MY_WEBSERVER_SOCKEROPS_H

#include <arpa/inet.h>
#include "../base/types.h"

const struct sockaddr* sockaddr_cast(const struct sockaddr_in6* addr)
{
    return static_cast<const struct sockaddr*>(implicit_cast<const void*>(addr));
}

struct sockaddr* sockaddr_cast(struct sockaddr_in6* addr)
{
    return static_cast<struct sockaddr*>(implicit_cast<void*>(addr));
}


#endif //MY_WEBSERVER_SOCKEROPS_H
