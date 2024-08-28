//
// Created by 着魔之人 on 24-8-4.
//

#ifndef MY_WEBSERVER_TIMERQUEUE_H
#define MY_WEBSERVER_TIMERQUEUE_H

#include "base/TimeStamp.h"
#include "Time/Callbacks.h"
#include "Time/Timer.h"
#include "pool/EventLoop.h"
#include "Time/TimerId.h"
#include "base/TimeStamp.h"
#include <set>




class TimerQueue {
public:
    TimerId addTimer(TimerCallback cb, TimeStamp when, double interval);
    void cancel(TimerId timerId);
private:
    using Entry = std::pair<TimeStamp,Timer*>;
    using TimerSet = std::set<Entry>;

    using ActiveTimer = std::pair<Timer*,int64_t>;
    using ActiveTimerSet = std::set<ActiveTimer>;

    EventLoop* loop_;
    const int timerfd_;
    Channel timerfdChannel_;
    TimerSet timers_;
    ActiveTimerSet activeTimers_;
    ActiveTimerSet cancelingTimers_;


    void handleRead();
    std::vector<Entry> getExpired(TimeStamp now);
    void reset(const std::vector<Entry>& expired, TimeStamp now);
    bool insert(Timer* timer);

};


#endif //MY_WEBSERVER_TIMERQUEUE_H
