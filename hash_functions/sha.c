#include "sha.h"

u32_t *sha1(u8_t *msg_buffer, int length){

    sha_ctx_t ctx = pad(msg_buffer, length);
    u32_t *msg_block = ctx.buffer;
    u32_t *digest = malloc(5 * sizeof(u32_t));
    u32_t *expanded_msg = malloc(80 * sizeof(u32_t));

    digest[0] = SHA1_A;
    digest[1] = SHA1_B;
    digest[2] = SHA1_C;
    digest[3] = SHA1_D;
    digest[4] = SHA1_E;

    while (msg_block < msg_block + ctx.length){

        expanded_msg = memcpy(expanded_msg, msg_block, 64);
        for (int i=0; i<80; i++){

            if (i>15){
                expanded_msg[i] = rol(1, expanded_msg[i-3] ^ expanded_msg[i-8] ^ expanded_msg[i-14] ^ expanded_msg[i-16]);
            }
            u32_t temp = rol(5, digest[0]) + f(i,digest[1], digest[2], digest[3]) + digest[4] + k(i) + expanded_msg[i];
            digest[4] = digest[3];
            digest[3] = digest[2];
            digest[2] = rol(30, digest[1]);
            digest[1] = digest[0];
            digest[0] = temp;

        }
        msg_block+=16;

    }

    digest[0] += SHA1_A;
    digest[1] += SHA1_B;
    digest[2] += SHA1_C;
    digest[3] += SHA1_D;
    digest[4] += SHA1_E;

    return digest;

}

static sha_ctx_t pad(u8_t *msg, int length){

    int last_block = length % 64;
    int zeros = 56-last_block;
    int len = last_block + zeros + 8;
    sha_ctx_t ctx = {
        malloc(len),
        len/4
    };

    ctx.buffer = memcpy(ctx.buffer, msg, last_block);
    unsigned char x = msg[0];
    unsigned char y = msg[1];
    unsigned char z = msg[2];

    memset(ctx.buffer+last_block-1, 0x80, 1);
    memset(ctx.buffer+last_block, 0x00, zeros-1);
    *(ctx.buffer + zeros) = (u64_t)last_block;
    for (int i=0; i<len; i++){
        unsigned char x = ctx.buffer[i];
        printf("%0x", ctx.buffer[i]);}
    printf("\n");
    return ctx;

}

static u32_t rol(int i, u32_t word){
    return (i << word)|(i >> (32 - word));
}

static u32_t k(int step){
    if (step<20)
        return 0x5A827999;
    if (step<40)
        return 0x6ED9EBA1;
    if (step<60)
        return 0x8F1BBCDC;
    if (step<80)
        return 0xCA62C1D6;
}

static u32_t f(int step, u32_t x, u32_t y, u32_t z){
    if (step<20)
        return (x & y) | (~x & z);
    if (step<40)
        return x ^ y ^ z;
    if (step<60)
        return (x & y) | (x & z) | (y & z);
    if (step<80)
        return x ^ y ^ z;
}