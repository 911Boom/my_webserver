//
// Created by 着魔之人 on 24-7-22.
//

#ifndef MY_WEBSERVER_EPOLLER_H
#define MY_WEBSERVER_EPOLLER_H

#include <vector>
#include <map>
#include "channel/Channel.h"
#include "base/TimeStamp.h"
#include "sys/epoll.h"

class EPoller {
private:
    using ChannelList = std::vector<Channel*>;
    using EventLists = std::vector<struct epoll_event>;
    using ChannelMap = std::map<int,Channel*>;
    int epollFd_{};
    int kInitEpollSize = 16;
    EventLoop ownerLoop_;
    EventLists events_;
    ChannelMap channels_;


public:
    explicit EPoller(EventLoop* loop);
    ~EPoller();
    TimeStamp poll(int timeoutMs, ChannelList *activeChannels);
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
    void updateChannel(Channel* channel) const;
    void removeChannel(Channel* channel);
    void assertInLoopThread() { ownerLoop_.assertInLoopThread(); }
    void update(int op, Channel *channel) const;
};


#endif //MY_WEBSERVER_EPOLLER_H
