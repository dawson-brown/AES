#include "modes.h"

// input: the plaintext, the block length, the plaintext length, and the ptr to store the location
// of the last element of the padded plaintext
// return: the new length of the padded plaintext 
void init_ciphertext(block_ctx_t *state)
{

    int pad = state->block_length - (state->text_length % state->block_length);
    int length = state->text_length + (pad==state->block_length ? 0 : pad);
    uint8_t *input = malloc(length);
    memcpy(input, state->text, state->text_length);

    if (pad != state->block_length)
        memset((input + length - pad), (uint8_t)pad, pad);

    state->text_length = length;
    state->text = input;
    
}


block_ctx_t ecb_enc(void (*cipher)(uint8_t*, const uint8_t*), block_ctx_t state, const uint8_t *key)
{

    init_ciphertext(&state);
    uint8_t *end = state.text + state.text_length;
    int block_length = state.block_length;
    uint8_t *block = state.text;

    while (block < end){

        cipher(block, key);
        block += block_length;

    }

    return state;
}

block_ctx_t ecb_dec(void (*cipher)(uint8_t*, const uint8_t*), block_ctx_t state, const uint8_t *key)
{

    uint8_t *end = state.text + state.text_length;
    int block_length = state.block_length;
    uint8_t *block = state.text;

    while (block < end){

        cipher(block, key);
        block += block_length;

    }

    return state;
}


block_ctx_t cbc_enc(
    void (*cipher)(uint8_t*, const uint8_t*), 
    block_ctx_t state, 
    const uint8_t *key, 
    const uint8_t *iv)
{
    
    init_ciphertext(&state);
    uint8_t *end = state.text + state.text_length;
    int block_length = state.block_length;
    uint8_t *block = state.text;
    uint8_t *iv_dyn = iv;

    while(block < end){

        for (int i = 0; i<block_length; i++)
            block[i] ^= iv_dyn[i];
        
        cipher(block, key);

        iv_dyn = block;
        block+=block_length;

    }

    return state;
}

block_ctx_t cbc_dec(
    void (*cipher)(uint8_t*, const uint8_t*), 
    block_ctx_t state, 
    const uint8_t *key, 
    const uint8_t *iv)
{
    
    uint8_t *start = state.text;
    int block_length = state.block_length;
    uint8_t *block = start + state.text_length - block_length;
    uint8_t *iv_dyn;

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