//
// Created by 着魔之人 on 24-8-4.
//

#ifndef MY_WEBSERVER_TIMERQUEUE_H
#define MY_WEBSERVER_TIMERQUEUE_H

#include "base/TimeStamp.h"
#include "Time/callbacks.h"
#include <set>

class Timer;

class TimerQueue {
public:
    void addTimer(TimerCallback);

private:
    using Entry = std::pair<TimeStamp,Timer*>;
    using TimerList = std::set<Entry>;
    using ActiveTimer = std::pair<Timer*,int64_t>;
    using ActiveTimerList = std::set<ActiveTimer>;
};


#endif //MY_WEBSERVER_TIMERQUEUE_H
