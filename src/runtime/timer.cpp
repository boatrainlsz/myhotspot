#include "timer.hpp"
#include "../os/linux.hpp"
#include "iostream"

void elapsedTimer::start() {
    _start_counter = Linux::elapsed_counter();
}

void elapsedTimer::stop() {
    _counter = Linux::elapsed_counter() - _start_counter;
}

double elapsedTimer::seconds() {
    return (double) _counter / (double) (1000000000);
}

TraceTime::TraceTime(char *title) : title(title) {
    std::cout << title << "时间统计开始..." << std::endl;
    timer.start();
}

TraceTime::~TraceTime() {
    timer.stop();
    std::cout << title << "时间统计结束,耗时" << timer.seconds() << "秒" << std::endl;
}
