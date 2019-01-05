#include <stdlib.h>
#include <stdio.h>
#include "file_handler/file_handler.h"
#include "number_handler/number_handler.h"

#define NB 4
#define NK 4
#define NK_BLOCK NK*NK
#define NR 10
#define STATE_SIZE 16

//Key expansion operations
#define ROT_WORD(v,w,x,y,z) ( (v)=(w), (w)=(x), (x)=(y), (y)=(z), (z)=(v) )
#define SBOX(w,x,y,z) (w=sbox[w], x=sbox[x], y=sbox[y], z=sbox[z]) //also used in encryption
#define RCON(x, i) (x^=rcon[i/(NK_BLOCK) - 1])

//encryption operations
#define SHIFT_1(v,w,x,y,z) ( (v)=(w), (w)=(x), (x)=(y), (y)=(z), (z)=(v) )
#define SHIFT_2(v,w,x,y,z) ( (v)=(z), (z)=(x), (x)=(v), (v)=(w), (w)=(y), (y)=(v) )
#define SHIFT_3(v,w,x,y,z) ( (v)=(w), (w)=(z), (z)=(y), (y)=(x), (x)=(v) )

typedef struct aes {
    unsigned char *state;
} aes_t;

unsigned char *key_expansion(unsigned char *key);

aes_t set_state(unsigned char *plaintext);

void add_round_key(unsigned char *state, unsigned char *round_key);

void sub_bytes(unsigned char *state);

void shift_rows(unsigned char *state);

void mix_columns(unsigned char *state);

void aes(aes_t *state, unsigned char *key);