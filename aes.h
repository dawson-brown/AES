#include <stdlib.h>
#include <string.h>

#define NB 4
#define NK 4
#define NK_BLOCK 16
#define NR 10

//Key expansion operations
#define ROT_WORD(v,w,x,y,z) ( (v)=(w), (w)=(x), (x)=(y), (y)=(z), (z)=(v) )
#define RCON(x, i) (x^=rcon[i/(NK_BLOCK) - 1])

//shift operations
#define SHIFT_1(v,w,x,y,z) ( (v)=(w), (w)=(x), (x)=(y), (y)=(z), (z)=(v) )
#define SHIFT_2(v,w,x,y,z) ( (v)=(z), (z)=(x), (x)=(v), (v)=(w), (w)=(y), (y)=(v) )
#define SHIFT_3(v,w,x,y,z) ( (v)=(w), (w)=(z), (z)=(y), (y)=(x), (x)=(v) )
#define SHIFT_ROWS(x,y) ( SHIFT_1(x,y[1],y[5],y[9],y[13]), SHIFT_2(x,y[2],y[6],y[10],y[14]), SHIFT_3(x,y[3],y[7],y[11],y[15]) )

//SBOX
#define SBOX(w,x,y,z) (w=sbox[w], x=sbox[x], y=sbox[y], z=sbox[z])
#define SBOX_ENC(x,j) for (j=0; j<NK_BLOCK; j+=NB){ SBOX(x[j], x[j+1], x[j+2], x[j+3]);}

//add round key
#define ADD_ROUND_KEY(x,y,j) for (j=0; j<(NK_BLOCK); j++){ x[j] ^= y[j];} y+=NK_BLOCK;

typedef unsigned char aes_t;

unsigned char *key_expansion(unsigned char *key);

void mix_columns(unsigned char *state);

void aes(aes_t *state, unsigned char *key);