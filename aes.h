#include <stdlib.h>
#include <string.h>

#define NB 4
#define NK 4
#define NK_BLOCK 16
#define NR 10

//Key expansion
#define EXPAND(k) for (int j=0; j<NK_BLOCK; j++) k[j] = j<4 ? k[j]^sbox[k[(j+13)-(j/3)*4]]^(j==0 ? rcon[i] : 0) : k[j]^k[j-NK];

//shift operations
#define SHIFT_1(v,w,x,y,z) ( (v)=(w), (w)=(x), (x)=(y), (y)=(z), (z)=(v) )
#define SHIFT_2(v,w,x,y,z) ( (v)=(z), (z)=(x), (x)=(v), (v)=(w), (w)=(y), (y)=(v) )
#define SHIFT_3(v,w,x,y,z) ( (v)=(w), (w)=(z), (z)=(y), (y)=(x), (x)=(v) )
#define SHIFT_ROWS(x,y) ( SHIFT_1(x,y[1],y[5],y[9],y[13]), SHIFT_2(x,y[2],y[6],y[10],y[14]), SHIFT_3(x,y[3],y[7],y[11],y[15]) )

//SBOX
#define SBOX(x) for (int j=0; j<NK_BLOCK; j++) x[j] = sbox[x[j]];

//add round key
#define ADD_ROUND_KEY(x,y) for (int j=0; j<(NK_BLOCK); j++) x[j] ^= y[j];

typedef unsigned char aes_t;

void mix_columns(unsigned char *state);

void aes(aes_t *state, unsigned char *key);