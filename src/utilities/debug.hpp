//
// Created by boatrain on 11/5/23.
//

#ifndef UTILITIES_DEBUG

#define UTILITIES_DEBUG

#include <cstddef>
#include "string.h"
#include "stdarg.h"
#include "stdio.h"

class FormatBufferBase {
protected:
    char *_buf;

    inline FormatBufferBase(char *buf) : _buf(buf) {}

public:
    operator const char *() const {
        return _buf;
    }
};

template<size_t bufsz = 256>
class FormatBuffer : public FormatBufferBase {
private:
    char _buffer[bufsz];
public:
    inline FormatBuffer(const char *format, ...);

    inline void print(const char *format, ...);

    inline void append(const char *format, ...);
};

typedef FormatBuffer<> err_msg;

template<size_t bufsz>
FormatBuffer<bufsz>::FormatBuffer(const char *format, ...):FormatBufferBase(_buffer) {
    va_list argp;
    va_start(argp, format);
    vsnprintf(_buf, bufsz, format, argp);
    va_end(argp);
}

template<size_t bufsz>
void FormatBuffer<bufsz>::append(const char *format, ...) {
    size_t len = strlen(_buf);
    char *buf_end = _buf + len;
    va_list argp;
    va_start(argp, format);
    vsnprintf(buf_end, bufsz, format, argp);
    va_end(argp);
}

template<size_t bufsz>
void FormatBuffer<bufsz>::print(const char *format, ...) {
    va_list argp;
    va_start(argp, format);
    vsnprintf(_buf, bufsz, format, argp);
    va_end(argp);
}


#define assert(p, msg) \
if(!(p)){\
  report_vm_error(__FILE__, __LINE__,"assert(" #p ") failed",msg);\
}

void report_vm_error(const char *file,
                     int line,
                     const char *err_msg,
                     const char *detail_msg);

#endif //UTILITIES_DEBUG
