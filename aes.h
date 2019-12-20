
#define NB 4
#define NK 4
#define BLOCK_SIZE 16
#define KEY_SIZE 16
#define NR 10


typedef unsigned char u8_t;

u8_t mul(u8_t a, u8_t b);

u8_t *expand_rcon();

u8_t *expand_key(u8_t *key);

void enc(u8_t *state, u8_t *key);

void dec(u8_t *state, u8_t *key);