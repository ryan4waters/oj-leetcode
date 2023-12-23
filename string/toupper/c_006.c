/*6.int64*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

static const char uppertable[] = {
    0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9,
    0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
    0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45,
    0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
    0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x41, 0x42, 0x43, 0x44, 0x45,
    0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
    0x5A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
};

void func_toupper(char *dst, const char *src, int len)
{
    int i;
    uint64_t eax, ebx;
    const uint8_t* ustr = (const uint8_t*)src;
    const int leftover = len % 8;
    const int imax = len / 8;
    const uint64_t* s = (const uint64_t*)src;
    uint64_t* d = (uint64_t*)dst;
    for (int i = 0; i != imax; ++i) {
        eax = s[i];
        ebx = (0x7f7f7f7f7f7f7f7fu & eax) + 0x0505050505050505u;
        ebx = (0x7f7f7f7f7f7f7f7fu & ebx) + 0x1a1a1a1a1a1a1a1au;
        ebx = ((ebx & ~eax) >> 2) & 0x2020202020202020u;
        *d++ = eax - ebx;
    }

    i = imax * 4;
    dst = (char*)d;
    switch (leftover) {
        case 7: *dst++ = (char)uppertable[ustr[i++]];
        case 6: *dst++ = (char)uppertable[ustr[i++]];
        case 5: *dst++ = (char)uppertable[ustr[i++]];
        case 4: *dst++ = (char)uppertable[ustr[i++]];
        case 3: *dst++ = (char)uppertable[ustr[i++]];
        case 2: *dst++ = (char)uppertable[ustr[i++]];
        case 1: *dst++ = (char)uppertable[ustr[i]];
        case 0: *dst = '\0';
    }
}