#include "aes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void print_plaintext(unsigned char *plaintext);

void test_enc(unsigned char *text, unsigned char *key);

void test_dec(unsigned char *text, unsigned char *key);

int main()
{
    unsigned char plaintext[16] = {'\x32','\x43','\xf6','\xa8','\x88','\x5a','\x30','\x8d','\x31','\x31','\x98','\xa2','\xe0','\x37','\x07','\x34'};
    unsigned char key[16] = {'\x2b','\x7e','\x15','\x16','\x28','\xae','\xd2','\xa6','\xab','\xf7','\x15','\x88','\x09','\xcf','\x4f','\x3c'};

    print_plaintext(plaintext);
    test_enc(plaintext, key);
    test_dec(plaintext, key);

    unsigned char plaintext1[16] = { '\x00','\x11','\x22','\x33','\x44','\x55','\x66','\x77','\x88','\x99','\xaa','\xbb','\xcc','\xdd','\xee','\xff' };
    unsigned char key1[16] = {'\x00','\x01','\x02','\x03','\x04','\x05','\x06','\x07','\x08','\x09','\x0a','\x0b','\x0c','\x0d','\x0e','\x0f'};

    print_plaintext(plaintext1);
    test_enc(plaintext1, key1);
    test_dec(plaintext1, key1);

    unsigned char plaintext2[16] = {'\x80','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00'};
    unsigned char key2[16] = {'\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00'};
    
    print_plaintext(plaintext2);
    test_enc(plaintext2, key2);
    test_dec(plaintext2, key2);


    return 0;
}

void print_plaintext(unsigned char *plaintext){
    for(int i=0; i<BLOCK_SIZE; i++){
        printf("%02x", plaintext[i]);
    }
    printf(" :plain\n");
}

void test_enc(unsigned char *text, unsigned char *key){
    enc(text, key);
    
    for(int i=0; i<BLOCK_SIZE; i++){
        printf("%02x", text[i]);
    }
    printf(" :enc\n");
}

void test_dec(unsigned char *text, unsigned char *key){
    dec(text, key);
    
    for(int i=0; i<BLOCK_SIZE; i++){
        printf("%02x", text[i]);
    }
    printf(" :dec\n");
}