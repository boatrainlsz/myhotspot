#include "linux.hpp"
#include "dlfcn.h"
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
