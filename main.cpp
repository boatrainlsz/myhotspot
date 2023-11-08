#include "iostream"
#include "src/utilities/debug.hpp"
#include "stdio.h"
#include "sstream"
#include "stdarg.h"
#include "src/utilities/globalDefinitions.hpp"

void err_msg(bool exp, const char *format, ...) {
    const int bufsz = 256;
    char _buf[bufsz];
    va_list argp;
    va_start(argp, format);
    vsnprintf(_buf, bufsz, format, argp);
    va_end(argp);
    assert(exp, _buf);
}

int main() {
    size_t len = 1;
    printf("len=" SIZE_FORMAT "\n", len);
    printf("len=" PTR_FORMAT "\n", 1111);
    err_msg(0,"len=" SIZE_FORMAT "\n", len);
    return 0;
}