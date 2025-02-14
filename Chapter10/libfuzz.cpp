#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size > 2 && data[0] == 'F' && data[1] == 'U' && data[2] == 'Z') {
        *(int *)0 = 0; 
    }
    return 0;
}
