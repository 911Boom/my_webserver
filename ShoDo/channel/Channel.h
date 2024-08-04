//
// Created by 着魔之人 on 24-7-22.
//

#ifndef MY_WEBSERVER_CHANNEL_H
#define MY_WEBSERVER_CHANNEL_H

#include <functional>
#include <sys/epoll.h>
#include "base/TimeStamp.h"
#include "pool/EventLoop.h"

class Channel {
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(TimeStamp)>;
    Channel(EventLoop* loop,int fd);
    ~Channel();
    void handleEvent();

    [[nodiscard]] EventLoop* ownerLoop() const { return loop_; }

    void setReadCallback(const EventCallback& Cb)
    { readCallback_ = Cb; }

    void setWriteCallback(const EventCallback& Cb)
    { writeCallback_ = Cb; }

    void setErrorCallback(const EventCallback& Cb)
    { errorCallback_ = Cb; }

    [[nodiscard]] int fd() const { return fd_; }

    [[nodiscard]] int events() const { return events_; }

    void setRevents(int revt) { revents_ = revt; }

    [[nodiscard]] bool isNoneEvent() const { return events_ == kNoneEvent; }

    void enableReading() { events_ |= kReadEvent; update(); }

    void enableWriting() { events_ |= kWriteEvent; update(); }

    void disableWriting() { events_ &= ~kWriteEvent; update(); }

    void disableAll() { events_ = kNoneEvent; update(); }

    [[nodiscard]] int index() const { return index_; }

    void setIndex(int idx) { index_ = idx; }



private:
    void update();
    static const int kNoneEvent = 0;
    static const int kReadEvent = EPOLLIN | EPOLLPRI;
    static const int kWriteEvent = EPOLLOUT;

    EventLoop* loop_;
    const int fd_;
    int events_; // 关心的io事件
    int revents_; // 活动的io事件
    int index_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
};



#endif //MY_WEBSERVER_CHANNEL_H
