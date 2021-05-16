#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct block_ctx {
    uint8_t *text;
    int text_length;
    int block_length;
} block_ctx_t;


//block cipher modes of operation and helpers
void init_ciphertext(block_ctx_t *state);

block_ctx_t ecb_enc(void (*cipher)(uint8_t*, const uint8_t*), block_ctx_t state, const uint8_t *key);

block_ctx_t ecb_dec(void (*cipher)(uint8_t*, const uint8_t*), block_ctx_t input, const uint8_t *key);


block_ctx_t cbc_enc(void (*cipher)(uint8_t*, const uint8_t*), block_ctx_t state, const uint8_t *key, const uint8_t *iv);

block_ctx_t cbc_dec(void (*cipher)(uint8_t*, const uint8_t*), block_ctx_t state, const uint8_t *key, const uint8_t *iv);
