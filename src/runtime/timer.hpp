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

class TraceTime {
private:
    elapsedTimer timer;
    char *title;
public:
    TraceTime(char *title);

    ~TraceTime();
};

#endif