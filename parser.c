#include "parser.h"

const char *argp_program_version = "argex 1.0";

const char *argp_program_bug_address = "<bug-gnu-utils@gnu.org>";

enum parser_opts {

    file = 'f',
    file_group = 0,

    text = 'p',
    text_group = 1,

    enc_key = 'k',
    key_group = 2

};

struct argp_option options[] =
{
  {"file", file, "The file to encrypt", 0, 0, file_group},
  {"plaintext", text, "The plaintext to encrypt", 0, 0, text_group},
  {"key", enc_key, "The encryption key", 0, 0, key_group},
  {0}
};

error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;
    switch (key)
    {
        case file:
            arguments->file = arg;
            break;
        case text:
            arguments->plaintext = arg;
            break;
        case enc_key:
            arguments->key = arg;
            if (arguments->plaintext != NULL || arguments->file != NULL)
                return ARGP_KEY_SUCCESS;
            break;
        case ARGP_KEY_ARG:
            argp_usage (state);
            break;

        case ARGP_KEY_END:
            if (state->arg_num != 0)
            /* No optionless arguments. accepted*/
            argp_usage (state);
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

