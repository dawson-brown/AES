#include "modes.h"

//this might be useful--this is just padding.
//make a padding module--if a plaintext gets to this module it should
//already be padded
// void init_ciphertext(block_ctx_t *state)
// {
//     int pad = state->block_length - (state->text_length % state->block_length);
//     int length = state->text_length + (pad==state->block_length ? 0 : pad);
//     uint8_t *input = malloc(length);
//     memcpy(input, state->text, state->text_length);

//     if (pad != state->block_length)
//         memset((input + length - pad), (uint8_t)pad, pad);

//     state->text_length = length;
//     state->text = input;  
// }

void ecb_enc(
    uint8_t * (*cipher)(uint8_t*, const uint8_t*), 
    uint8_t * state, 
    const int state_len, 
    const uint8_t *key)
{
    uint8_t *end = state + state_len;
    uint8_t *block = state;

    while (block < end){

        uint8_t * next_block = cipher(block, key);
        block = next_block;

    }
}

void ecb_dec(
    uint8_t * (*cipher)(uint8_t*, const uint8_t*), 
    uint8_t * state,
    const int state_len, 
    const uint8_t *key)
{
    uint8_t *end = state + state_len;
    uint8_t *block = state;

    while (block < end){

        uint8_t * next_block = cipher(block, key);
        block = next_block;

    }

}

void cbc_enc(
    uint8_t * (*cipher)(uint8_t*, const uint8_t*), 
    uint8_t * state, 
    const int state_len,
    const uint8_t *key, 
    const uint8_t *iv,
    const int iv_len)
{
    uint8_t *end = state + state_len;
    uint8_t *block = state;
    uint8_t *iv_dyn = iv;

    while(block < end){

        for (int i = 0; i<iv_len; i++)
            block[i] ^= iv_dyn[i];
        
        uint8_t * next_block = cipher(block, key);

        iv_dyn = block;
        block = next_block;

    }

}

void cbc_dec(
    uint8_t * (*cipher)(uint8_t*, const uint8_t*), 
    uint8_t * state, 
    const int state_len,
    const uint8_t *key, 
    const uint8_t *iv,
    const int iv_len)
{
    uint8_t *start = state;
    uint8_t *block = start + state_len - iv_len;
    uint8_t *iv_dyn;

    while(block >= start){
                
        uint8_t * next_block = cipher(block, key);

        iv_dyn = block - (next_block - block);
        for (int i = 0; i<iv_len; i++)
            block[i] ^= iv_dyn[i];

        block-=(next_block - block);

    }

    for (int i = 0; i<iv_len; i++)
        block[i] ^= iv[i];

    return state;

}