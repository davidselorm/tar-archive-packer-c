#ifndef TAR_PACKER_H
#define TAR_PACKER_H

#include <stdint.h>
#include <stddef.h>

#define TAR_BLOCK_SIZE 512

/* POSIX USTAR 512-byte header structure */
typedef struct {
    char name[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12];
    char chksum[8];
    char typeflag;
    char linkname[100];
    char magic[6];
    char version[2];
    char uname[32];
    char gname[32];
    char devmajor[8];
    char devminor[8];
    char prefix[155];
    char pad[12];
} TarHeader;

unsigned int calculate_tar_checksum(const TarHeader* header);
int validate_tar_checksum(const TarHeader* header);
void format_octal(char* dest, size_t len, uint64_t value);
void init_tar_header(TarHeader* header, const char* filename, size_t file_size);

#endif
