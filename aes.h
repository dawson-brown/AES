#include <stdlib.h>

#define NB 4
#define NK 4
#define BLOCK_SIZE 16
#define KEY_SIZE 16
#define NR 10

#define ROUNDS i=0; i<NR; i++
#define KEY j=0; j<KEY_SIZE; j++
#define BLOCK j=0; j<BLOCK_SIZE; j++

//shift operations
#define SHIFT_1(v,w,x,y,z) ( (v)=(w), (w)=(x), (x)=(y), (y)=(z), (z)=(v) )
#define SHIFT_2(v,w,x,y,z) ( (v)=(z), (z)=(x), (x)=(v), (v)=(w), (w)=(y), (y)=(v) )
#define SHIFT_3(v,w,x,y,z) ( (v)=(w), (w)=(z), (z)=(y), (y)=(x), (x)=(v) )
#define SHIFT_ROWS(x,y) ( SHIFT_1(x,y[1],y[5],y[9],y[13]), SHIFT_2(x,y[2],y[6],y[10],y[14]), SHIFT_3(x,y[3],y[7],y[11],y[15]) )

typedef unsigned char aes_t;

unsigned char sub(unsigned char byte);

unsigned char mul(unsigned char a, unsigned char b);

void aes(aes_t *state, unsigned char *key);