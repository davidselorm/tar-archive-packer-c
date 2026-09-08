#include <stdio.h>
#include <string.h>
#include "tar.h"

void format_octal(char* dest, size_t len, uint64_t value) {
    snprintf(dest, len, "%0*llo", (int)(len - 1), (unsigned long long)value);
}

unsigned int calculate_tar_checksum(const TarHeader* header) {
    const unsigned char* bytes = (const unsigned char*)header;
    unsigned int sum = 0;
    
    for (size_t i = 0; i < TAR_BLOCK_SIZE; i++) {
        // Treat checksum field bytes as spaces during calculation
        if (i >= offsetof(TarHeader, chksum) && i < offsetof(TarHeader, chksum) + 8) {
            sum += ' ';
        } else {
            sum += bytes[i];
        }
    }
    return sum;
}

int validate_tar_checksum(const TarHeader* header) {
    unsigned int expected = 0;
    sscanf(header->chksum, "%o", &expected);
    return expected == calculate_tar_checksum(header);
}

void init_tar_header(TarHeader* header, const char* filename, size_t file_size) {
    memset(header, 0, sizeof(TarHeader));
    strncpy(header->name, filename, sizeof(header->name) - 1);
    format_octal(header->mode, sizeof(header->mode), 0644);
    format_octal(header->uid, sizeof(header->uid), 1000);
    format_octal(header->gid, sizeof(header->gid), 1000);
    format_octal(header->size, sizeof(header->size), file_size);
    format_octal(header->mtime, sizeof(header->mtime), 1700000000);
    header->typeflag = '0'; // Regular file
    memcpy(header->magic, "ustar", 6);
    memcpy(header->version, "00", 2);
    strncpy(header->uname, "user", sizeof(header->uname) - 1);
    strncpy(header->gname, "user", sizeof(header->gname) - 1);
    
    unsigned int chksum = calculate_tar_checksum(header);
    snprintf(header->chksum, sizeof(header->chksum), "%06o", chksum);
}
