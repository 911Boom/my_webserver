//
// Created by 着魔之人 on 24-8-5.
//

#ifndef MY_WEBSERVER_TIMERID_H
#define MY_WEBSERVER_TIMERID_H


#include <cstdint>

class Timer;

class TimerId{
public:
    TimerId() : timer_(nullptr), sequece_(0) { }
    TimerId(Timer* timer, int64_t sequece) : timer_(timer), sequece_(sequece) { }
    friend class TimerQueue;
private:
    Timer* timer_;
    int64_t sequece_;
};





#endif //MY_WEBSERVER_TIMERID_H
