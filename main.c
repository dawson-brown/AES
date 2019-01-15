#include "aes.h"
#include <stdio.h>

static unsigned char *plaintext = "\x32\x43\xf6\xa8\x88\x5a\x30\x8d\x31\x31\x98\xa2\xe0\x37\x07\x34";
static unsigned char *key = "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c";

int main(){

    unsigned char *ciphertext = malloc(NK_BLOCK);
    memcpy(ciphertext, plaintext, NK_BLOCK);
    aes(ciphertext, key);
    
    for(int i=0; i<NK_BLOCK; i++){
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}