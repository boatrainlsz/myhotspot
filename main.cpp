#include "iostream"
#include "src/utilities/debug.hpp"
#include "src/utilities/outputstream.hpp"
#include "src/os/linux.hpp"
#include "src/runtime/timer.hpp"
#include "src/runtime/atomic.hpp"
#include "src/prims/jni.h"
#include "stdio.h"
#include "unistd.h"
#include "sstream"
#include "stdarg.h"
#include "string.h"
#include "src/utilities/globalDefinitions.hpp"

volatile jint t = 0;

void *func(void *arg) {
    int i = 0;
    while (i++ < 1000) {
        Atomic::inc(&t);
        usleep(1);
    }
}

int main() {
    pthread_t id[20] = {0};
    for (int i = 0; i < 20; ++i) {
        int ret = pthread_create(&id[i], NULL,
                                 func, NULL);
    }
    sleep(10);
    std::cout << t << std::endl;
    return 0;
}