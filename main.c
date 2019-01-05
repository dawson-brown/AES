#include "aes.h"
#include "parser.h"
#include <argp.h>

int main(int argc, char **argv){
    
    struct arguments arguments;
    arguments.file = NULL;
    arguments.plaintext = NULL;
    arguments.key = NULL;
    argp_parse (&argp, argc, argv, 0, 0, &arguments);

    if (arguments.file != NULL){
        char *plaintext = file_open_read(arguments.file);
        printf("%s", plaintext);
        free(plaintext);
    } else if (arguments.plaintext != NULL){
        hex_num_t *key = convert_to_hex(arguments.key);
        key->num = key_expansion(key->num);

        hex_num_t *plaintext = convert_to_hex(arguments.plaintext);
        aes_t state = set_state(plaintext->num);

        aes(&state, key->num);

        memcpy(plaintext->num, state.state, STATE_SIZE);

        print_hex("Encrypted msg: ", plaintext);
    }

    return 0;
}