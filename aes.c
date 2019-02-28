#include "aes.h"

//multiply in Rijndael finite field
unsigned char mul(unsigned char a, unsigned char b) {
	unsigned char p = 0;
	do {
    if (b & 1) p ^= a;
    
    a= a & 0x80 ? (a << 1) ^ 0x1b : a << 1;

	} while ( b >>= 1); 
	return p;
}

//Rijndael S-BOX.
unsigned char sub(unsigned char byte){
  unsigned char sub_byte = '\0', inverse = '\0';

    do {
      if (mul(byte, sub_byte)==1) inverse=sub_byte;
    } while (++sub_byte);

  return inverse^
    ((inverse << 1)|(inverse >> 7))
    ^((inverse << 2)|(inverse >> 6))
    ^((inverse<<3)|(inverse >> 5))
    ^((inverse<<4)|(inverse >> 4))^0x63;
  
}

void aes(aes_t *state, unsigned char *key)
{
  unsigned char temp, j, i, rc='\x01', rc_m = '\x80', s[16];

  //add round key
  for (BLOCK) state[j] ^= key[j];  
  for(ROUNDS)
  {
    //update round key
    for (KEY) key[j] = j<4 ? key[j]^sub(key[(j+13)-(j/3)*4])^(j==0 ? rc : 0):(key[j]^key[j-NK]); 
    rc=(rc<rc_m)?(2*rc):(2*rc)^'\x1B';

    //perform S-Box
    for (BLOCK) state[j] = sub(state[j]); 
    SHIFT_ROWS(temp, state);
    if (i!=(NR-1)){
      for (BLOCK) s[j] = state[j];
      for(BLOCK) state[j]=mul(s[j],'\2')^mul(s[4*(j/4)+(j+1)%4],'\3')^mul(s[4*(j/4)+(j+2)%4],'\1')^mul(s[4*(j/4)+(j+3)%4],'\1');
    }

    //add round key
    for (BLOCK) state[j] ^= key[j];
  }
}

