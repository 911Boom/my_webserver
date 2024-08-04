//
// Created by 着魔之人 on 24-7-21.
//

#include <cassert>
#include <sys/poll.h>
#include "EventLoop.h"

thread_local EventLoop* t_loopInThisThread = nullptr;
const int kPollTimeoutMs = 10000;


EventLoop::EventLoop()
    : looping_(false),
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
    }
    looping_ = false;
}


void EventLoop::runInLoop(EventLoop::Func func) {

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
