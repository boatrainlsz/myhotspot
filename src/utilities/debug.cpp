#include "debug.hpp"
#include "iostream"

void report_vm_error(const char *file, int line,
                     const char *err_msg,
                     const char *detail_msg) {
    std::cout << file << " " << line << " " <<
              err_msg << " " << detail_msg << std::endl;
    ::abort();
}