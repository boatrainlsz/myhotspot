#include "timer.hpp"
#include "../os/linux.hpp"

void elapsedTimer::start() {
    _start_counter = Linux::elapsed_counter();
}

void elapsedTimer::stop() {
    _counter = Linux::elapsed_counter() - _start_counter;
}

double elapsedTimer::seconds() {
    return (double) _counter / (double) (1000000000);
}