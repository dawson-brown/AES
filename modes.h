#include <stdlib.h>
#include <string.h>

typedef unsigned char u8_t;

typedef struct block_ctx {
    u8_t *text;
    int length;
    int block_length;
} block_ctx_t;


//block cipher modes of operation and helpers
void init_ciphertext(block_ctx_t *state);

block_ctx_t ecb_enc(void (*cipher)(u8_t*, const u8_t*), block_ctx_t state, const u8_t *key);

block_ctx_t ecb_dec(void (*cipher)(u8_t*, const u8_t*), block_ctx_t input, const u8_t *key);


block_ctx_t cbc_enc(void (*cipher)(u8_t*, const u8_t*), block_ctx_t state, const u8_t *key, const u8_t *iv);

block_ctx_t cbc_dec(void (*cipher)(u8_t*, const u8_t*), block_ctx_t state, const u8_t *key, const u8_t *iv);
