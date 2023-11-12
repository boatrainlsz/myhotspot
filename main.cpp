#include "iostream"
#include "src/utilities/debug.hpp"
#include "src/utilities/outputstream.hpp"
#include "src/os/linux.hpp"
#include "src/runtime/timer.hpp"
#include "stdio.h"
#include "unistd.h"
#include "sstream"
#include "stdarg.h"
#include "string.h"
#include "src/utilities/globalDefinitions.hpp"

int main() {
    outputStream *t = new outputStream();
    const char *x = "test";
    t->print_cr("===== %s ====", x);
    return 0;
}