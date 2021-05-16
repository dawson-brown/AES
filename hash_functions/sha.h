#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long u64_t;
typedef unsigned int u32_t;
typedef unsigned char u8_t;

typedef struct sha_ctx {
    u32_t *buffer;
    int length;
} sha_ctx_t;

#define SHA1_A 0x67452301
#define SHA1_B 0xEFCDAB89
#define SHA1_C 0x98BADCFE
#define SHA1_D 0x10325476
#define SHA1_E 0xC3d2E1F0

u32_t *sha1(u8_t *msg_buffer, int length);

static sha_ctx_t pad(u8_t *msg, int length);

static u32_t rol(int i, u32_t word);

static u32_t k(int step);

static u32_t f(int step, u32_t x, u32_t y, u32_t z);