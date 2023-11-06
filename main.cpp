#include "iostream"
#include "src/utilities/globalDefinitions.hpp"

int main() {
    size_t len = 1;
    printf("len=" SIZE_FORMAT "\n", len);
    printf("len=" PTR_FORMAT "\n", 1111);
    return 0;
}