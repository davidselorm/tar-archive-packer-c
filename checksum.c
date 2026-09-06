#include "tar.h"
#include <string.h>

unsigned int calculate_tar_checksum(const struct posix_header* h) {
    const unsigned char* bytes = (const unsigned char*)h;
    unsigned int sum = 0;
    for (int i = 0; i < 512; i++) {
        if (i >= 148 && i < 156) sum += 32; // treat checksum field as ASCII spaces
        else sum += bytes[i];
    }
    return sum;
}
