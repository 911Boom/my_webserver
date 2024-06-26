//
// Created by 着魔之人 on 24-6-17.
//

#ifndef MY_WEBSERVER_WEBSERVER_H
#define MY_WEBSERVER_WEBSERVER_H
#include "server/listenaddr.h"




class webserver {
    listen_addr* addr;
    int thread_size,open_log,log_level;

};


#endif //MY_WEBSERVER_WEBSERVER_H
