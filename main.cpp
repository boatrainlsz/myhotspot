#include "iostream"
#include "src/utilities/debug.hpp"
#include "src/os/linux.hpp"
#include "src/runtime/timer.hpp"
#include "stdio.h"
#include "unistd.h"
#include "sstream"
#include "stdarg.h"
#include "string.h"
#include "src/utilities/globalDefinitions.hpp"

int main() {
    Linux::init();
    {
        elapsedTimer t;
        t.start();
        sleep(5);
        t.stop();
        std::cout << t.seconds() << std::endl;
    }
    return 0;
}