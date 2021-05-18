//!  A block cipher modes of operation module. 
/*!
  This module contains functions for block cipher modes of operation.
  Each mode of operation is indifferent to the block cipher used.
*/

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * This function encrypts a plaintext with a block cipher in ecb mode
 * 
 * \param[in] cipher a block cipher
 * \param[in,out] state the plaintext to encrypt
 * \param[in] state_len the length of \p state
 * \param[in] key: the encryption key
 */ 
void ecb_enc(
    uint8_t * (*cipher)(uint8_t*, const uint8_t*), 
    uint8_t * state, 
    const int state_len, 
    const uint8_t *key);

/**
 * This function decrypts a ciphertext with a block cipher in ecb mode
 * 
 * \param[in] cipher a block cipher
 * \param[in,out] state the ciphertext to decrypt
 * \param[in] state_len the length of \p state
 * \param[in] key the decryption key
 */ 
void ecb_dec(
    uint8_t * (*cipher)(uint8_t*, const uint8_t*), 
    uint8_t * state,
    const int state_len, 
    const uint8_t *key);

/**
 * This function encrypts a plaintext with a block cipher in cbc mode
 * 
 * \param[in] cipher a block cipher
 * \param[in,out] state the plaintext to encrypt
 * \param[in] state_len the length of \p state
 * \param[in] key the encryption key
 * \param[in] iv the initialization vector
 * \param[in] iv_len the length of \p iv
 */ 
void cbc_enc(
    uint8_t * (*cipher)(uint8_t*, const uint8_t*), 
    uint8_t * state, 
    const int state_len,
    const uint8_t *key, 
    const uint8_t *iv,
    const int iv_len);

/**
 * This function decrypts a ciphertext with a block cipher in cbc mode
 * 
 * \param[in] cipher a block cipher
 * \param[in,out] state the ciphertext to decrypt
 * \param[in] state_len the length of \p state
 * \param[in] key the encryption key
 * \param[in] iv the initialization vector
 * \param[in] iv_len the length of \p iv
 */
void cbc_dec(
    uint8_t * (*cipher)(uint8_t*, const uint8_t*), 
    uint8_t * state, 
    const int state_len,
    const uint8_t *key, 
    const uint8_t *iv,
    const int iv_len);