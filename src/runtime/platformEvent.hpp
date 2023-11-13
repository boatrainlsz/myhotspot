
#ifndef RUNTIME_PLATFORMEVENT
#define RUNTIME_PLATFORMEVENT

#include "pthread.h"
#include "../prims/jni.h"
#include "../utilities/debug.hpp"

class PlatformEvent {
private:
    /**
     * 0.初始化
     * -1.park方法中减1
     * 1.unpark方法
     */
    volatile int _Event;
    pthread_cond_t _cond[1];
    pthread_mutex_t _mutex[1];
public:
    PlatformEvent() {
        _Event = 0;
        int status = pthread_cond_init(_cond, NULL);
        assert(status == 0, "cond_init");
        status = pthread_mutex_init(_mutex, NULL);
        assert(status == 0, "mutex_init");
    }


    void park();

    int park(jlong millis);

    void unpark();
};

#endif
