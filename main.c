#include "aes.h"
#include <string.h>
#include <stdio.h>

void test(unsigned char *text, unsigned char *key);

int main()
{
    unsigned char plaintext[16] = {'\x32','\x43','\xf6','\xa8','\x88','\x5a','\x30','\x8d','\x31','\x31','\x98','\xa2','\xe0','\x37','\x07','\x34'};
    unsigned char key[16] = {'\x2b','\x7e','\x15','\x16','\x28','\xae','\xd2','\xa6','\xab','\xf7','\x15','\x88','\x09','\xcf','\x4f','\x3c'};
    test(plaintext, key);

    unsigned char plaintext1[16] = {'\x80','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00'};
    unsigned char key1[16] = {'\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00'};
    test(plaintext1, key1);

    return 0;
}

void test(unsigned char *text, unsigned char *key){
    enc(text, key);
    
    for(int i=0; i<BLOCK_SIZE; i++){
        printf("%02x", text[i]);
    }
    printf("\n");
}