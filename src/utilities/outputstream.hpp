#ifndef UTILITIES_OUTPUTSTREAM

#define UTILITIES_OUTPUTSTREAM

#include "stdio.h"
#include "stdarg.h"

#define  BUFFSIZE 1024

class outputStream {
protected:
    static int _output_fd;
    static int _error_fd;

public:
    void print(const char *format, ...);

    void print_cr(const char *format, ...);

    void write(const char *str, size_t len);

    void cr();

    const char *do_vsnprintf(char *buffer,
                             size_t buflen,
                             const char *format,
                             va_list ap,
                             bool add_cr,
                             size_t &result_len);
};

#endif