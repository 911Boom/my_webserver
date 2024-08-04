//
// Created by 着魔之人 on 24-7-21.
//

#ifndef MY_WEBSERVER_EVENTLOOP_H
#define MY_WEBSERVER_EVENTLOOP_H


#include <atomic>
#include <functional>
#include <vector>
#include <mutex>
#include <thread>
#include <memory>
#include "./base/TimeStamp.h"
#include "./channel/Channel.h"
#include "./channel/EPoller.h"


class EventLoop {
public:
    using Func = std::function<void()>;
    EventLoop();
    ~EventLoop();
    void loop();
    void assertInLoopThread() {
        if(!isInLoopThread()) {
            abortNotInLoopThread();
        }
    }
    [[nodiscard]] bool isInLoopThread() const {
        return threadId_ == std::this_thread::get_id();
    }
    static EventLoop *getEventLoopOfCurrentThread();
    void runInLoop(Func func);
    void quit() {
        quit_ = true;
    }
    void updateChannel(Channel* channel_);
private:

    using ChannelLists = std::vector<Channel*>;
    void abortNotInLoopThread();

    const std::thread::id threadId_;
    std::atomic<bool> quit_;
    std::atomic<bool> looping_;
    std::unique_ptr<EPoller> poller_;
    ChannelLists activeChannels_;
};


#endif //MY_WEBSERVER_EVENTLOOP_H
