#define NB 4
#define NK 4
#define BLOCK_SIZE 16
#define KEY_SIZE 16
#define NR 10

#define ROUNDS i=0; i<NR; i++
#define KEY j=0; j<KEY_SIZE; j++
#define KEY_I j=KEY_SIZE-1; j>=0; j--
#define BLOCK j=0; j<BLOCK_SIZE; j++

typedef unsigned char aes_t;

unsigned char sub(unsigned char byte);

unsigned char sub_i(unsigned char byte);

unsigned char mul(unsigned char a, unsigned char b);

void enc(aes_t *state, unsigned char *key);

void dec(aes_t *state, unsigned char *key);