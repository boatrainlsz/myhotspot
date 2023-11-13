#include "linux.hpp"
#include "dlfcn.h"
#include "sys/time.h"
#include "../utilities/debug.hpp"

static long initial_time_count = 0;

int (*Linux::_clock_gettime)(clockid_t clock_id, struct timespec *ts) = NULL;

void Linux::init() {
    clock_init();
    initial_time_count = javaTimeNanos();
}

void Linux::clock_init() {
    void *handle = dlopen("librt.so", RTLD_LAZY);
    if (handle) {
        int (*clock_gettime_func)(clockid_t clock_id, struct timespec *ts)
        =(int (*)(clockid_t clock_id, struct timespec *ts)) dlsym(handle, "clock_gettime");
        if (clock_gettime_func) {
            struct timespec tp;
            if (clock_gettime_func(CLOCK_MONOTONIC, &tp) == 0) {
                _clock_gettime = clock_gettime_func;
                return;
            }
        }
    }
}

long Linux::javaTimeNanos() {
    struct timespec tp;
    int status = _clock_gettime(CLOCK_MONOTONIC, &tp);
    assert(status == 0, "gettime error!");
    long result = long(tp.tv_sec) * (1000 * 1000 * 1000) + long(tp.tv_sec);
    return result;
}

long Linux::elapsed_counter() {
    return javaTimeNanos() - initial_time_count;
}

struct timespec *Linux::compute_abstime(timespec *abstime, jlong millis) {
    if (millis < 0) {
        millis = 0;
    }
    jlong seconds = millis / 1000;
    millis %= 1000;
    struct timespec now;
    int status = _clock_gettime(CLOCK_MONOTONIC, &now);
    assert(status == 0, "gettime error!");
    abstime->tv_sec = now.tv_sec + seconds;
    long nanos = now.tv_nsec + millis * 1000 * 1000;
    if (nanos >= 1000 * 1000 * 1000) {
        abstime->tv_sec += 1;
        nanos -= 1000 * 1000 * 1000;
    }
    abstime->tv_nsec = nanos;
    return abstime;
}

long Linux::javaTimeMillis() {
    timeval time;
    int status = gettimeofday(&time, NULL);
    assert(status != -1, "linux error!");
    return long(time.tv_sec) * (1000) + long(time.tv_usec / 1000);
}
