#include "outputstream.hpp"
#include "stdio.h"
#include "string.h"
#include "unistd.h"

int outputStream::_output_fd = 1;
int outputStream::_error_fd = 2;


const char *outputStream::do_vsnprintf(char *buffer,
                                       size_t buflen,
                                       const char *format,
                                       va_list ap,
                                       bool add_cr,
                                       size_t &result_len) {
    const char *result;
    if (add_cr) {
        buflen--;
    }
    if (!strchr(format, '%')) {
        result = format;
        result_len = strlen(result);
        if (add_cr && result_len >= buflen) {
            result_len = buflen - 1;
        }
    } else if (format[0] == '%' && format[1] == 's'
               && format[2] == '\0') {
        result = va_arg(ap, const char *);
        result_len = strlen(result);
        if (add_cr && result_len >= buflen) {
            result_len = buflen - 1;
        }
    } else if (vsnprintf(buffer, buflen, format, ap) >= 0) {
        result = buffer;
        result_len = strlen(result);
    } else {
        result = buffer;
        result_len = buflen - 1;
        buffer[result_len] = 0;
    }
    if (add_cr) {
        if (result != buffer) {
            strncpy(buffer, result, buflen);
            result = buffer;
        }
        buffer[result_len++] = '\n';
        buffer[result_len] = 0;
    }
    return result;
}

void outputStream::write(const char *str, size_t len) {
    ::write(_output_fd, str, (int) strlen(str));
}

void outputStream::cr() {
    this->write("\n", 1);
}

void outputStream::print(const char *format, ...) {
    char buffer[BUFFSIZE];
    va_list argp;
    va_start(argp, format);
    size_t len;
    const char *result = do_vsnprintf(buffer, BUFFSIZE, format,
                                      argp, false, len);
    write(result, len);
    va_end(argp);
}

void outputStream::print_cr(const char *format, ...) {
    char buffer[BUFFSIZE];
    va_list argp;
    va_start(argp, format);
    size_t len;
    const char *result = do_vsnprintf(buffer, BUFFSIZE, format,
                                      argp, true, len);
    write(result, len);
    va_end(argp);
}



