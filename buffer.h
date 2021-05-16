#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct buffer_t {
    uint8_t * text;
    int text_length;
} buffer_t;

buffer_t str_new_string(int len);