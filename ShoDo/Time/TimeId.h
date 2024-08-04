//
// Created by 着魔之人 on 24-8-5.
//

#ifndef MY_WEBSERVER_TIMEID_H
#define MY_WEBSERVER_TIMEID_H


#include <cstdint>

class Timer;

class TimeId{
public:
    TimeId() : timer_(nullptr), sequece_(0) { }
    TimeId(Timer* timer, int64_t sequece) : timer_(timer), sequece_(sequece) { }
    friend class TimerQueue;
private:
    Timer* timer_;
    int64_t sequece_;
};





#endif //MY_WEBSERVER_TIMEID_H
