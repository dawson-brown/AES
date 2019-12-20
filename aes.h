#include <string.h>
#include <stdlib.h>

#define NB 4
#define NK 4
#define BLOCK_SIZE 16
#define KEY_SIZE 16
#define NR 10


typedef unsigned char u8_t;

static u8_t mul(u8_t a, u8_t b);

static void expand_key(const u8_t key[static 16], u8_t *key_schedule);

void enc(u8_t state[static 16], u8_t key[static 16]);

void dec(u8_t state[static 16], u8_t key[static 16]);