
#ifndef RUNTIME_ORDERACCESS
#define RUNTIME_ORDERACCESS

class OrderAccess {
public:
    static void loadload();

    static void storestore();

    static void loadstore();

    static void storeload();

    static void release();

    static void acquire();

    static void fence();
};

inline void OrderAccess::loadload() {
    acquire();
}

inline void OrderAccess::storestore() {
    release();
}

inline void OrderAccess::storeload() {
    fence();
}

inline void OrderAccess::loadstore() {
    acquire();
}


inline void OrderAccess::acquire() {

}

inline void OrderAccess::release() {

}

inline void OrderAccess::fence() {
    __asm__ volatile ("lock; addl $0,0(%%rsp)" : : :"cc", "memory");
}

#endif
