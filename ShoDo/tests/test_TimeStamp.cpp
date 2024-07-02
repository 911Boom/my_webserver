//
// Created by 着魔之人 on 24-6-26.
//
#include "base/TimeStamp.h"

#include <iostream>

int main() {
    TimeStamp now = TimeStamp::now();
    std::cout << now.toString() << std::endl;
    std::cout << now.toFormattedString() << std::endl;
    std::cout << now.toFormattedString(true) << std::endl;
    for (int i = 0; i < 1000; i++) {
        TimeStamp t = TimeStamp::now();
        std::cout << t.toString() << std::endl;
        std::cout << t.toFormattedString() << std::endl;
        std::cout << t.getMicSec() - now.getMicSec() << std::endl;
    }
    return 0;
}