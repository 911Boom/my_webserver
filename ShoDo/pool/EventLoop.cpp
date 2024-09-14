//
// Created by 着魔之人 on 24-7-21.
//

#include <cassert>
#include <sys/poll.h>
#include "EventLoop.h"
#include "server/Socket.h"
thread_local EventLoop* t_loopInThisThread = nullptr;
const int kPollTimeoutMs = 10000;


EventLoop::EventLoop()
    : looping_(false),
      quit_(false),
      callingPendingFunc_(false),
      poller_(new EPoller(this)),
      timerQueue_(new TimerQueue(this)),

      threadId_(std::this_thread::get_id()) {
    if(t_loopInThisThread) {
        t_loopInThisThread = this;
    } else {
//        LOG_FATAL<<
    }
}

EventLoop::~EventLoop() {
    assert(!looping_);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop() {
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;
    quit_ = false;
    poller_ -> poll(kPollTimeoutMs, &activeChannels_);
    looping_ = false;
    while(!quit_) {
        activeChannels_.clear();
        poller_->poll(kPollTimeoutMs, &activeChannels_);
        for(auto &channel : activeChannels_) {
            channel->handleEvent();
        }
        doPendingFunc();
    }
    looping_ = false;
}

void EventLoop::quit() {
    quit_ = true;
    if(!isInLoopThread()) {
        wakeup();
    }
}

void EventLoop::runInLoop(EventLoop::Func func) {
     if(isInLoopThread()) {
         func();
     } else {
         queueInLoop(std::move(func));
     }
}

void EventLoop::abortNotInLoopThread() {
//    LOG<<"NO"<<endl;
}

EventLoop *EventLoop::getEventLoopOfCurrentThread() {
    return t_loopInThisThread;
}

void EventLoop::updateChannel(Channel *channel_) {
    assert(channel_->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel_);
}

void EventLoop::queueInLoop(Func cb) {
    std::scoped_lock<std::mutex> lock(mutex_);
    pendingFunctors_.push_back(std::move(cb));
    if(!isInLoopThread() || callingPendingFunc_) {
        wakeup();
    }
}

void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = ::write(wakeupFd_,&one,sizeof one);
    if(n != sizeof one) {
        //LOG_ERROR<<"ERROR"<<endl;
    }
}


void EventLoop::handleRead() {
    uint64_t one = 1;
    ssize_t n = ::read(wakeupFd_,&one,sizeof one);
    if(n != sizeof one) {
        //LOG_ERROR<<"ERROR"<<endl;
    }
}

void EventLoop::doPendingFunc() {
    std::vector<Func> funcs;
    callingPendingFunc_ = true;
    {
        std::scoped_lock<std::mutex> lock(mutex_);
        funcs.swap(pendingFunctors_);
    }
    for(const auto& func: funcs) {
        func();
    }
    callingPendingFunc_ = false;
}
