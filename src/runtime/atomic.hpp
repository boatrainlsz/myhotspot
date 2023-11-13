#ifndef RUNTIME_ATOMIC
#define RUNTIME_ATOMIC

#include "../prims/jni.h"

class Atomic {
public:
    static void store(jlong value, volatile jlong *dst) {
        *dst = value;
    }

    static long load(volatile jlong *src) {
        return *src;
    }

    static inline jint cmpxchg(jint exchange_value,
                               volatile jint *dst,
                               jint compare_value) {
        __asm__ volatile ("lock;cmpxchgl %1,(%3)"
                : "=a" (exchange_value)
                : "r" (exchange_value), "a" (compare_value), "r"(dst)
                :"cc", "memory");
        return exchange_value;
    }

    static void inc(volatile jint *dst) {
        __asm__ volatile(
                "lock;addl $1,(%0)"
                :
                : "r" (dst)
                :"cc", "memory");
    }

    static void dec(volatile jint *dst) {
        __asm__ volatile(
                "lock;subl $1,(%0)"
                :
                : "r" (dst)
                :"cc", "memory");
    }

    static jint xchg(jint exchange_value, volatile jint *dst) {
        __asm__ volatile(
                "xchgl(%2),%0"
                : "=r" (exchange_value)
                : "0" (exchange_value), "r"(dst)
                : "memory");
        return exchange_value;
    }
};

#endif
