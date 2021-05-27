#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define NB 4
#define NK 4
#define AES_BLOCK_SIZE 16
#define AES_128_KEY_SIZE 16
#define NR 10

/**
 * encrypt a block using AES-128
 * 
 * \param[in] block the block to encrypt
 * \param[in] key the encryption key
 * 
 * \return a pointer to the next byte after \p block
 **/ 
uint8_t * aes_128_enc(uint8_t block[static 16], const uint8_t key[static 16]);

/**
 * decrypt a block using AES-128
 * 
 * \param[in] block the block to encrypt
 * \param[in] key the decryption key
 * 
 * \return a pointer to the next byte after \p block
 **/ 
uint8_t * aes_128_dec(uint8_t block[static 16], const uint8_t key[static 16]);
