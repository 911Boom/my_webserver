//
// Created by 着魔之人 on 24-7-22.
//

#include <cassert>
#include "EPoller.h"

const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;


TimeStamp EPoller::poll(int timeoutMs, ChannelList *activeChannels) {
    int numEvents = ::epoll_wait(epollFd_,
                                 events_.data(),
                                 static_cast<int>(events_.size()),
                                 timeoutMs);
    TimeStamp now(TimeStamp::now());
    assert(numEvents >= 0);
    if(numEvents > 0) {
        fillActiveChannels(numEvents, activeChannels);
        if(implicit_cast<size_t>(numEvents) == events_.size()) {
            events_.resize(events_.size() * 2);
        }
    }
    return now;
}
void EPoller::update(int op, Channel *channel) const {
    struct epoll_event event{};
    memZero(&event, sizeof(event));
    event.events = channel->events();
    event.data.ptr = channel;
    int fd = channel->fd();
    if(::epoll_ctl(epollFd_, op, fd, &event) < 0) {
//        LOG<<"EPoller::update()";
    }
}

void EPoller::updateChannel(Channel *channel) const {
    const int index = channel -> index();
    int fd = channel -> fd();
    if(index == kNew || index == kDeleted) {
        channel -> setIndex(kAdded);
        update(EPOLL_CTL_ADD, channel);
    } else {
        if(channel -> isNoneEvent()) {
            update(EPOLL_CTL_DEL, channel);
            channel -> setIndex(kDeleted);
        } else {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EPoller::removeChannel(Channel *channel) {
    assertInLoopThread();
    int fd = channel->fd();
    channels_.erase(fd);
    if(channel -> index() == kAdded) {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->setIndex(kNew);
}

EPoller::EPoller(EventLoop *loop)
    : ownerLoop_(loop),
      events_(kInitEpollSize),
      epollFd_(::epoll_create1(EPOLL_CLOEXEC)) {
    if(epollFd_ < 0) {
//        LOG<<"EPoller::EPoller()";
    }
}

void EPoller::fillActiveChannels(int numEvents, EPoller::ChannelList *activeChannels) const {
    assert(numEvents <= events_.size());
    for(int i = 0 ;i < numEvents; ++i) {
        auto *channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->setRevents(static_cast<int>(events_[i].events));
        activeChannels->push_back(channel);
    }
}



EPoller::~EPoller() {
    ::close(epollFd_);
}
