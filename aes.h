#include <string.h>
#include <stdlib.h>

#define NB 4
#define NK 4
#define BLOCK_SIZE 16
#define KEY_SIZE 16
#define NR 10

typedef unsigned char u8_t;

void aes_enc(u8_t state[static 16], const u8_t key[static 16]);

void aes_dec(u8_t state[static 16], const u8_t key[static 16]);
