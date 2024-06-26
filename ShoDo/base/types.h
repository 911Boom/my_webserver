//
// Created by 着魔之人 on 24-6-18.
//

#ifndef MY_WEBSERVER_TYPES_H
#define MY_WEBSERVER_TYPES_H


#include <cstring>
#include <string>

using std::string;

inline void memZero(void* p,size_t n) {
    memset(p,0,n);
}

template<typename To, typename From>
inline To implicit_cast(From const &f)
{
    return f;
}

#endif //MY_WEBSERVER_TYPES_H
