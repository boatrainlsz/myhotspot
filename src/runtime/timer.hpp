#ifndef RUNTIME_TIMER
#define  RUNTIME_TIMER

class elapsedTimer {
private:
    long _start_counter;
    long _counter;
public:
    void start();

    void stop();

    double seconds();
};

#endif