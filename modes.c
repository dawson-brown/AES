#include "modes.h"

// input: the plaintext, the block length, the plaintext length, and the ptr to store the location
// of the last element of the padded plaintext
// return: the new length of the padded plaintext 
void init_ciphertext(block_ctx_t *state)
{

    int pad = state->block_length - (state->length % state->block_length);
    int length = state->length + (pad==state->block_length ? 0 : pad);
    u8_t *input = malloc(length);
    memcpy(input, state->text, state->length);

    if (pad != state->block_length)
        memset((input + length - pad), (u8_t)pad, pad);

    state->length = length;
    state->text = input;
    
}


block_ctx_t ecb_enc(void (*cipher)(u8_t*, const u8_t*), block_ctx_t state, const u8_t *key)
{

    init_ciphertext(&state);
    u8_t *end = state.text + state.length;
    int block_length = state.block_length;
    u8_t *block = state.text;

    while (block < end){

        cipher(block, key);
        block += block_length;

    }

    return state;
}

block_ctx_t ecb_dec(void (*cipher)(u8_t*, const u8_t*), block_ctx_t state, const u8_t *key)
{

    u8_t *end = state.text + state.length;
    int block_length = state.block_length;
    u8_t *block = state.text;

    while (block < end){

        cipher(block, key);
        block += block_length;

    }

    return state;
}


block_ctx_t cbc_enc(void (*cipher)(u8_t*, const u8_t*), block_ctx_t state, const u8_t *key, const u8_t *iv){
    
    init_ciphertext(&state);
    u8_t *end = state.text + state.length;
    int block_length = state.block_length;
    u8_t *block = state.text;
    u8_t *iv_dyn = iv;

    while(block < end){

        for (int i = 0; i<block_length; i++)
            block[i] ^= iv_dyn[i];
        
        cipher(block, key);

        iv_dyn = block;
        block+=block_length;

    }

    return state;
}


block_ctx_t cbc_dec(void (*cipher)(u8_t*, const u8_t*), block_ctx_t state, const u8_t *key, const u8_t *iv){
    
    u8_t *start = state.text;
    int block_length = state.block_length;
    u8_t *block = start + state.length - block_length;
    u8_t *iv_dyn;

    while(block >= start){
                
        cipher(block, key);

        iv_dyn = block - block_length;
        for (int i = 0; i<block_length; i++)
            block[i] ^= iv_dyn[i];

        block-=block_length;

    }

    for (int i = 0; i<block_length; i++)
        block[i] ^= iv[i];

    return state;

}