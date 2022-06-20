//
// Created by Administrator on 2022/6/20.
//

#ifndef DPI_TEST_CLOCK_H
#define DPI_TEST_CLOCK_H

#include <iostream>
#include <chrono>

class Clock {
public:
    void start() {
        time_start = std::chrono::system_clock::now();
    }

    void stop() {
        time_end = std::chrono::system_clock::now();
    }

    double seconds() const {
        std::chrono::duration<double> delta = time_end - time_start;
        return delta.count();
    }
private:
    std::chrono::time_point<std::chrono::system_clock> time_start, time_end;
};

#endif //DPI_TEST_CLOCK_H
