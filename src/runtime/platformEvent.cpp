#include "platformEvent.hpp"
#include "atomic.hpp"
#include "../os/linux.hpp"
#include "errno.h"

void PlatformEvent::park() {
    int v;
    for (;;) {
        v = _Event;
        if (Atomic::cmpxchg(v - 1, &_Event, v) == v) {
            break;
        }
    }
    if (v == 0) {
        int status = pthread_mutex_lock(_mutex);
        assert(status == 0, "mutex_lock");
        //为什么要while，见Linux-UNIX系统编程手册30.2.3
        while (_Event < 0) {
            status = pthread_cond_wait(_cond, _mutex);
            assert(status == 0 || status == EINTR, "cond_wait");
        }
        _Event = 0;
        status = pthread_mutex_unlock(_mutex);
        assert(status == 0, "mutex_unlock");
    }
}

int PlatformEvent::park(jlong millis) {
    int v;
    for (;;) {
        v = _Event;
        if (Atomic::cmpxchg(v - 1, &_Event, v) == v) {
            break;
        }
    }
    int ret = 0;
    if (v == 0) {
        v = -3;
        struct timespec abstime;
        Linux::compute_abstime(&abstime, millis);
        int status = pthread_mutex_lock(_mutex);
        assert(status == 0, "mutex_lock");
        while (_Event < 0) {
            int status = pthread_cond_timedwait(_cond, _mutex, &abstime);
            assert(status == 0 || status == EINTR ||
                   status == ETIMEDOUT, "cond_timedwait");
            if (status == ETIMEDOUT) {
                break;
            }
        }
        if (_Event >= 0)ret = 0;
        _Event = 0;
        status = pthread_mutex_unlock(_mutex);
        assert(status == 0, "mutex_unlock");
    }
    return ret;
}

void PlatformEvent::unpark() {
    jint v = Atomic::xchg(1, &_Event);
    if (v >= 0) {
        return;
    }
    pthread_mutex_lock(_mutex);
    pthread_cond_signal(_cond);
    pthread_mutex_unlock(_mutex);
}