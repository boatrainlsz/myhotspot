//
// Created by boatrain on 11/5/23.
//

#ifndef UTILITIES_DEBUG

#define UTILITIES_DEBUG


#define assert(p,msg) \
if(!(p)){\
  report_vm_error(__FILE__, __LINE__,"assert(" #p ") failed",msg);\
}

void report_vm_error(const char* file,
                     int line,
                     const char* err_msg,
                     const char* detail_msg);

#endif //UTILITIES_DEBUG
