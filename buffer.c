#include "buffer.h"

buffer_t str_new_string(int len)
{
    buffer_t buffer;
    buffer.text = malloc(sizeof(uint8_t) * len);
    buffer.text_length = len;

    return buffer;
}