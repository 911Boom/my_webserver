//
// Created by 着魔之人 on 24-7-22.
//

#include "channel/Channel.h"

#include <sys/poll.h>




Channel::Channel(EventLoop *loop, int fd)
    :loop_(loop),
     fd_(fd),
     events_(0),
     revents_(0),
     index_(-1){
}

Channel::~Channel() = default;

void Channel::handleEvent() {
    if(events_ & EPOLLERR) {
        if(errorCallback_) errorCallback_();
    }
    if(events_ & EPOLLIN) {
        if(readCallback_) readCallback_();
        //处理读事件
    }
    if(events_ & EPOLLOUT) {
        if(writeCallback_) writeCallback_();
    }
}


void Channel::update() {
    loop_->updateChannel(this);
}
