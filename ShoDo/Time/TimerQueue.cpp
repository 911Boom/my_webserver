//
// Created by 着魔之人 on 24-8-4.
//

#include "Time/TimerQueue.h"
#include "sys/timerfd.h"

int createTimerfd()
{
    int timerfd = ::timerfd_create(CLOCK_MONOTONIC,
                                   TFD_NONBLOCK | TFD_CLOEXEC);
    if (timerfd < 0)
    {
        // LOG_SYSFATAL << "Failed in timerfd_create";
    }
    return timerfd;
}


TimerQueue::TimerQueue(EventLoop *loop):
    loop_(loop),
    timerfd_(createTimerfd()),
    timerfdChannel_(loop,timerfd_),
    timers_(),
    // callingExpiredTimers_(false)
{
    timerfdChannel_.setReadCallback(std::bind(&TimerQueue::handleRead,this));
    timerfdChannel_.enableReading();
}
TimerId TimerQueue::addTimer(TimerCallback cb, TimeStamp when, double interval) {
    auto* timer = new Timer(std :: move(cb),when,interval);
//    loop_ -> runInloop(std::bind(&TimerQueue::addTimerInLoop,this,timer));
    return {timer, timer->sequence()};
}


std::vector<TimerQueue::Entry> TimerQueue::getExpired(TimeStamp now) {
    Entry sentry = {now, reinterpret_cast<Timer*>(UINTPTR_MAX)};
    std::vector<Entry> expired(timers_.begin(),timers_.lower_bound(sentry));
    timers_.erase(timers_.begin(),timers_.lower_bound(sentry));
    return expired;
}

void TimerQueue::handleRead() {

}

void TimerQueue::reset(const std::vector<Entry> &expired, TimeStamp now) {

}

bool TimerQueue::insert(Timer *timer) {

}

void TimerQueue::cancel(TimerId timerId) {

}