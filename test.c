#include <stdio.h>
#include "modes.h"
#include "aes.h"
#include "minunit.h"

#define AES_BLOCK_LENGTH 16

int tests_run = 0;

static char * test_aes_enc() {

    unsigned char text[AES_BLOCK_LENGTH] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    unsigned char key[AES_BLOCK_LENGTH] = "\x10\xa5\x88\x69\xd7\x4b\xe5\xa3\x74\xcf\x86\x7c\xfb\x47\x38\x59";
    u8_t *expected = "\x6d\x25\x1e\x69\x44\xb0\x51\xe0\x4e\xaa\x6f\xb4\xdb\xf7\x84\x65";

    aes_enc(text, key);
    mu_assert("aes encryption: failed", memcmp(text, expected, AES_BLOCK_LENGTH) == 0);    

    return 0;
}

static char * test_aes_dec() {

    unsigned char text[AES_BLOCK_LENGTH] = "\x5d\x9b\x05\x57\x8f\xc9\x44\xb3\xcf\x1c\xcf\x0e\x74\x6c\xd5\x81";
    unsigned char key[AES_BLOCK_LENGTH] = "\xb6\x36\x4a\xc4\xe1\xde\x1e\x28\x5e\xaf\x14\x4a\x24\x15\xf7\xa0";
    u8_t *expected = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    aes_dec(text, key);
    mu_assert("aes decryption: failed", memcmp(text, expected, AES_BLOCK_LENGTH) == 0);    

    return 0;
}

static char * test_ecb_enc() {

    u8_t text[2*AES_BLOCK_LENGTH] = "\x32\x43\xf6\xa8\x88\x5a\x30\x8d\x31\x31\x98\xa2\xe0\x37\x07\x34\x32\x43\xf6\xa8\x88\x5a\x30\x8d\x31\x31\x98\xa2\xe0\x37\x07\x34";
    unsigned char key[AES_BLOCK_LENGTH] = "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c";
    block_ctx_t state = {
        text,
        32,
        AES_BLOCK_LENGTH
    };
    u8_t expected[2*AES_BLOCK_LENGTH] = "\x39\x25\x84\x1d\x02\xdc\x09\xfb\xdc\x11\x85\x97\x19\x6a\x0b\x32\x39\x25\x84\x1d\x02\xdc\x09\xfb\xdc\x11\x85\x97\x19\x6a\x0b\x32";
    
    state = ecb_enc(aes_enc, state, key);
    mu_assert("ecb encryption: failed", memcmp(state.text, expected, 32) == 0);
    return 0;
}

static char * test_ecb_dec() {

    u8_t text[2*AES_BLOCK_LENGTH] = "\x39\x25\x84\x1d\x02\xdc\x09\xfb\xdc\x11\x85\x97\x19\x6a\x0b\x32\x39\x25\x84\x1d\x02\xdc\x09\xfb\xdc\x11\x85\x97\x19\x6a\x0b\x32";
    u8_t key[AES_BLOCK_LENGTH] = "\x2b\x7e\x15\x16\x28\xae\xd2\xa6\xab\xf7\x15\x88\x09\xcf\x4f\x3c";
    block_ctx_t state = {
        text,
        32,
        AES_BLOCK_LENGTH
    };
    u8_t expected[2*AES_BLOCK_LENGTH] = "\x32\x43\xf6\xa8\x88\x5a\x30\x8d\x31\x31\x98\xa2\xe0\x37\x07\x34\x32\x43\xf6\xa8\x88\x5a\x30\x8d\x31\x31\x98\xa2\xe0\x37\x07\x34";
    
    state = ecb_dec(aes_dec, state, key);
    mu_assert("ecb decryption: failed", memcmp(state.text, expected, 32) == 0);
    return 0;
}

static char * test_cbc_enc(){

    u8_t text[2*AES_BLOCK_LENGTH] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    u8_t key[AES_BLOCK_LENGTH] = "\xCA\xEA\x65\xCD\xBB\x75\xE9\x16\x9E\xCD\x22\xEB\xE6\xE5\x46\x75";
    u8_t iv[AES_BLOCK_LENGTH] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    block_ctx_t state = {
        text,
        32,
        AES_BLOCK_LENGTH
    };
    u8_t expected[2*AES_BLOCK_LENGTH] = "\x6E\x29\x20\x11\x90\x15\x2D\xF4\xEE\x05\x81\x39\xDE\xF6\x10\xBB\xF0\x5E\x49\x26\x33\xE0\x6C\x96\x2A\xA9\xEC\x33\xFA\x80\x43\xA0";
    
    state = cbc_enc(aes_enc, state, key, iv);
    mu_assert("cbc encryption: failed", memcmp(state.text, expected, 32) == 0);
    return 0;
}

static char * test_cbc_dec(){

    u8_t text[2*AES_BLOCK_LENGTH] = "\x6E\x29\x20\x11\x90\x15\x2D\xF4\xEE\x05\x81\x39\xDE\xF6\x10\xBB\xF0\x5E\x49\x26\x33\xE0\x6C\x96\x2A\xA9\xEC\x33\xFA\x80\x43\xA0";
    u8_t key[AES_BLOCK_LENGTH] = "\xCA\xEA\x65\xCD\xBB\x75\xE9\x16\x9E\xCD\x22\xEB\xE6\xE5\x46\x75";
    u8_t iv[AES_BLOCK_LENGTH] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    block_ctx_t state = {
        text,
        32,
        AES_BLOCK_LENGTH
    };
    u8_t expected[2*AES_BLOCK_LENGTH] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
    
    state = cbc_dec(aes_dec, state, key, iv);
    mu_assert("cbc decryption: failed", memcmp(state.text, expected, 32) == 0);
    return 0;
}

static char * all_tests() {

    mu_run_test(test_aes_enc);
    mu_run_test(test_aes_dec);

    mu_run_test(test_ecb_enc);
    mu_run_test(test_ecb_dec);

    mu_run_test(test_cbc_enc);
    mu_run_test(test_cbc_dec);

    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}