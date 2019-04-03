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

//Rijndael inverse S-BOX.
unsigned char sub_i(unsigned char byte){
  unsigned char sub_byte = '\0';

  unsigned char inverse = ((byte << 1)|(byte >> 7))
    ^((byte << 3)|(byte >> 5))
    ^((byte << 6)|(byte >> 2))^0x05;

  do {
    if (mul(inverse, sub_byte)==1) byte=sub_byte;
  } while (++sub_byte);

  if (inverse==0x00) byte=0x00;
  return byte;
  
}

void enc(aes_t *state, unsigned char *key)
{
  unsigned char j, i, rc='\x01', rc_i = '\x80', rc_x='\x00', s[16];
  
  for(ROUNDS)
  {  
    //add round key
    for (BLOCK) s[j] = state[j]^key[j];

    //update round key
    for (KEY) 
      key[j] = j<4 ? 
          key[j]^sub(key[j==3 ? 12 : j+13])^(j==0 ? rc : 0):
          (key[j]^key[j-NK]); 

    //update rc      
    rc_x=(rc==rc_i)?'\x1B':'\x00';
    rc = (rc<<1)^rc_x;

    //perform S-Box and shift rows
    for (BLOCK) state[j] = sub(s[(j+4*(j%4)) % 16]);

    //mix columns
    if (i!=(NR-1)){
      for (BLOCK) s[j] = state[j];
      for(BLOCK) state[j]=mul(s[j],'\2')^
                          mul(s[4*(j/4)+(j+1)%4],'\3')^
                          mul(s[4*(j/4)+(j+2)%4],'\1')^
                          mul(s[4*(j/4)+(j+3)%4],'\1');
    }
  }
  //add round key
  for (BLOCK) state[j] ^= key[j];
}

void dec(aes_t *state, unsigned char *key){

  unsigned char i, rc='\x36', rc_i = '\x1b', rc_x='\x00', s[16];
  char j;

  //add round key
  for (BLOCK) s[j] = state[j]^key[j];

  for(ROUNDS)
  {
    //inverse shift rows and subbytes
    for (BLOCK) state[(j+4*(j%4)) % 16] = sub_i(s[j]);

    //update round key
    for (KEY_I) 
      key[j] = j<4 ? 
          key[j]^sub(key[j==3 ? 12 : j+13])^(j==0 ? rc : 0):
          (key[j]^key[j-NK]);

    //update rc
    rc = (rc>>1)^rc_x;
    rc_x=(rc==rc_i)?'\x8d':'\x00';

    //add round key
    for (BLOCK) s[j] = state[j]^key[j];

    //inverse mix columns 
    if (i!=(NR-1)){
      for(BLOCK) state[j]=mul(s[j],'\x0E')^
                          mul(s[4*(j/4)+(j+1)%4],'\x0B')^
                          mul(s[4*(j/4)+(j+2)%4],'\x0D')^
                          mul(s[4*(j/4)+(j+3)%4],'\x09');
      for (BLOCK) s[j] = state[j];
    }
    //add round key
    for (BLOCK) state[j] ^= key[j];
  }
}

