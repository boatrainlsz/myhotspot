#ifndef OS_LINUX
#define  OS_LINUX

#include "time.h"
#include "../prims/jni.h"

class Linux {
public:
    static int (*_clock_gettime)(clockid_t clock_id, struct timespec *ts);

    static void clock_init();

    static long javaTimeNanos();

    static long javaTimeMillis();

    static void init();

    static long elapsed_counter();

    static struct timespec *compute_abstime(timespec *abstime, jlong millis);
};

#endif