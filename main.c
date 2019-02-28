#include "aes.h"
#include <string.h>
#include <stdio.h>

int main()
{
    unsigned char plaintext[16] = {'\x32','\x43','\xf6','\xa8','\x88','\x5a','\x30','\x8d','\x31','\x31','\x98','\xa2','\xe0','\x37','\x07','\x34'};
    unsigned char key[16] = {'\x2b','\x7e','\x15','\x16','\x28','\xae','\xd2','\xa6','\xab','\xf7','\x15','\x88','\x09','\xcf','\x4f','\x3c'};

    aes(plaintext, key);
    
    for(int i=0; i<BLOCK_SIZE; i++){
        printf("%02x", plaintext[i]);
    }
    printf("\n");
    return 0;
}