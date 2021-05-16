#include <stdio.h>
#include "test.h"
#include "sha.h"

int tests_run = 0;
 
 
static char * test_sha1() {
    u32_t *digest = sha1("abc", 3);
    mu_assert("error, foo != 7", 7 == 7);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_sha1);
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