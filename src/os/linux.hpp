#ifndef OS_LINUX
#define  OS_LINUX

#include "time.h"

class Linux {
public:
    static int (*_clock_gettime)(clockid_t clock_id, struct timespec *ts);

    static void clock_init();

    static long javaTimeNanos();

    static void init();

    static long elapsed_counter();
};

#endif