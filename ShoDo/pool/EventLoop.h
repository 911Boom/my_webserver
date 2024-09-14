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
#include "./channel/Channel.h"
#include "./channel/EPoller.h"
#include "Time/Callbacks.h"
#include "Time/TimerQueue.h"

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
    void quit();
    void updateChannel(Channel* channel_);
    TimerId runAt(TimeStamp time,TimerCallback cb) {
        return timerQueue_->addTimer(cb,time,0.0);
    }

    TimerId runAfter(double delay,TimerCallback cb) {
        TimeStamp time(addTime(TimeStamp::now(),delay));
        return runAt(time,std::move(cb));
    }

    TimerId runEvery(double interval, TimerCallback cb) {
        TimeStamp time(addTime(TimeStamp::now(),interval));
        return timerQueue_->addTimer(cb,time,interval);
    }

    void wakeup();
    void queueInLoop(Func cb);

private:

    using ChannelLists = std::vector<Channel*>;
    void abortNotInLoopThread();
    void handleRead();
    void doPendingFunc();

    std::atomic<bool> looping_;
    const std::thread::id threadId_;
    std::atomic<bool> quit_;
    std::atomic<bool> callingPendingFunc_;
    std::unique_ptr<EPoller> poller_;
    std::unique_ptr<TimerQueue> timerQueue_;
    std::mutex mutex_;
    ChannelLists activeChannels_;
    int wakeupFd_;
    std::unique_ptr<Channel> wakeupChannel_;
    std::vector<Func> pendingFunctors_;
};


#endif //MY_WEBSERVER_EVENTLOOP_H
