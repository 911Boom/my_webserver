//
// Created by 着魔之人 on 24-8-4.
//

#include "Time/TimerQueue.h"



TimerId TimerQueue::addTimer(TimerCallback cb, TimeStamp when, double interval) {
    auto* timer = new Timer(std :: move(cb),when,interval);
//    loop_ -> runInloop(std::bind(&TimerQueue::addTimerInLoop,this,timer));
    return {timer, timer->sequence()};
}

void TimerQueue::cancel(TimerId timerId) {

}

std::vector<TimerQueue::Entry> TimerQueue::getExpired(TimeStamp now) {
    Entry sentry = {now, reinterpret_cast<Timer*>(UINTPTR_MAX)};
    std::vector<Entry> expired(timers_.begin(),timers_.lower_bound(sentry));
    timers_.erase(timers_.begin(),timers_.lower_bound(sentry));
    return expired;
//    return expired;
}

void TimerQueue::handleRead() {

}

void TimerQueue::reset(const std::vector<Entry> &expired, TimeStamp now) {

}

bool TimerQueue::insert(Timer *timer) {
    return false;
}

