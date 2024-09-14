//
// Created by 着魔之人 on 24-6-26.
//

#ifndef MY_WEBSERVER_TIMESTAMP_H
#define MY_WEBSERVER_TIMESTAMP_H


#include <ctime>
#include <sys/time.h>
#include "base/types.h"
#include <cinttypes>
#include <boost/operators.hpp>

using string = std::string;


class TimeStamp : public boost::equality_comparable<TimeStamp>,
                  public boost::totally_ordered<TimeStamp> {
private:
    int64_t micSec_;
public:
    static const int kMicSecPerSec = 1000 * 1000;

    TimeStamp() : micSec_(0) {}

    explicit TimeStamp(int64_t micSecArg_) : micSec_(micSecArg_) {}

    [[nodiscard]] bool valid() const {
        return micSec_ > 0;
    }

    static TimeStamp invalid() {
        return {};
    }

    static TimeStamp now() {
        struct timeval tv{};
        gettimeofday(&tv, nullptr);
        int64_t Secs = tv.tv_sec;
        return TimeStamp(Secs * kMicSecPerSec + tv.tv_usec);
    }

    static TimeStamp fromUnixTime(time_t t) {
        return fromUnixTime(t, 0);
    }

    static TimeStamp fromUnixTime(time_t t, int64_t micSecs) {
        return TimeStamp(static_cast<int64_t>(t) * kMicSecPerSec + micSecs);
    }

    [[nodiscard]] int64_t getMicSec() const { return micSec_; }

    [[nodiscard]] time_t getSecsTime() const {
        return static_cast<time_t>(micSec_ / kMicSecPerSec);
    }

    [[nodiscard]] int64_t getSecInt() const {
        return static_cast<int64_t>(micSec_ / kMicSecPerSec);
    }

    [[nodiscard]] int getModSecInt() const {
        return static_cast<int>(micSec_ % kMicSecPerSec);
    }

    [[nodiscard]] std::string toString() const {
        char buf[32] = {0};
        int64_t secs = getSecInt();
        int micSecs = getModSecInt();
        snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId32 "", secs, micSecs);
        return buf;
    }

    [[nodiscard]] std::string toFormattedString(bool showMicSec = false) const {
        char buf[64] = {0};
        time_t secs = getSecsTime();
        struct tm tm_time{};
        gmtime_r(&secs, &tm_time);
        if (showMicSec) {
            int micSecs = getModSecInt();
            snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
                     tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                     tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                     micSecs);
        } else {
            snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
                     tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                     tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
        }
        return buf;
    }

    int64_t micSec() const { return micSec_; }
};


inline bool operator<(const TimeStamp &lhs, const TimeStamp &rhs) {
    return lhs.getMicSec() < rhs.getMicSec();
}

inline bool operator==(const TimeStamp &lhs, const TimeStamp &rhs) {
    return lhs.getMicSec() == rhs.getMicSec();
}

inline TimeStamp addTime(TimeStamp timestamp, double seconds)
{
    auto delta = static_cast<int64_t>(seconds * TimeStamp:: kMicSecPerSec);
    return TimeStamp(timestamp.micSec() + delta);
}

#endif //MY_WEBSERVER_TIMESTAMP_H
