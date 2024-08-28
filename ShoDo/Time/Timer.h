//
// Created by 着魔之人 on 24-8-5.
//

#ifndef MY_WEBSERVER_TIMER_H
#define MY_WEBSERVER_TIMER_H

#include "base/TimeStamp.h"
#include <atomic>
#include <utility>
#include "Time/Callbacks.h"

class Timer {
public:

    Timer(TimerCallback cb, TimeStamp when, double interval)
        : callback_(std::move(cb)),
          expiration_(when),
          interval_(interval),
          repeat_(interval > 0.0),
          sequence_(++numCreated_)
    { }
    void run() const { callback_(); }
    [[nodiscard]] TimeStamp expiration() const { return expiration_; }
    [[nodiscard]] bool repeat() const { return repeat_; }
    [[nodiscard]] int64_t sequence() const { return sequence_; }
    static int64_t numCreated() { return numCreated_; }


private:
    const TimerCallback callback_;
    TimeStamp expiration_;
    const double interval_{};
    const bool repeat_{};
    const int64_t sequence_{};
    static std::atomic<int64_t> numCreated_;
};


#endif //MY_WEBSERVER_TIMER_H
