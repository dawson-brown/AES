#include "number_handler.h"

char base64_dic[66] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/',
	'='
};

hex_num_t *hex_init(int len){

	hex_num_t *hexNum = (hex_num_t *)malloc(sizeof(hex_num_t));
	hexNum->num = (unsigned char*)malloc(len);
	hexNum->size = len;
	return hexNum;

}

base_64_t *base64_init(int len, short padding){

	base_64_t *base64 = (base_64_t *)malloc(sizeof(base_64_t));
	base64->num = (unsigned char*)malloc(len);
	base64->size = len;
	base64->padding = padding;
	return base64;

}

base_64_t *base64_encode(hex_num_t *hex) {

	int hex_len = hex->size;
	unsigned char *buffer = hex->num;

	short padding = ((hex_len + 3) % 3)*2 % 3;
	int len = 4*ceil((double)hex_len/3);
	base_64_t *b64 = base64_init(len, padding);
	unsigned char *start = b64->num;

	int buffer_count = 0;

	while (buffer_count <= hex_len){

		*start++ = buffer[buffer_count] >> 2;
		*start++ = ((buffer[buffer_count] & ((1 << 2) - 1)) << 4) ^ (buffer[++buffer_count] >> 4);
		*start++ = ((buffer[buffer_count] & ((1 << 4) - 1)) << 2) ^ (buffer[++buffer_count] >> 6);
		*start++ = buffer[buffer_count++] & ((1 << 6) - 1);

	}

	b64->padding = padding;

	//add padding
	if (padding > 0){
		*--start = 0x40;
		if (padding==2)
			*--start = 0x40;
	}

	return b64;

}

hex_num_t *base64_decode(base_64_t *base64){
	
	int base64_len = base64->size;
	unsigned char *buffer = base64->num;

	short padding = base64->padding;
	int len = ((3*base64_len)/4)-(((base64_len + 4)+padding)%4);
	hex_num_t *hex = hex_init(len);
	unsigned char *start = hex->num;

	int buffer_count = 0;

	while (buffer_count <= (base64_len-padding)){

		*start++ = (buffer[buffer_count] << 2) ^ (buffer[++buffer_count] >> 4);
		*start++ = (buffer[buffer_count] << 4) ^ (buffer[++buffer_count] >> 2);
		*start++ = (buffer[buffer_count] << 6) ^ (buffer[++buffer_count]);
		++buffer_count;

	}

	return hex;
}

unsigned char ascii_to_hex(char a){

	unsigned char hex = a;

	if (hex > DIGIT_LOW && hex < DIGIT_HIGH){
		return hex-HEX_OFFSET_DIG;
	} else if (hex > UPPERCASE_LOW_BOUND && hex < UPPERCASE_HEX_HIGH_BOUND){
		return hex-HEX_OFFSET_CHAR_CAP;
	} else if (hex > LOWERCASE_LOW_BOUND && hex < LOWER_HEX_HIGH_BOUND){
		return hex-HEX_OFFSET_CHAR_LOW;
	} else {
		printf("Invalid hex character: %c   Exiting...\n", hex);
		exit(0);
	}

}

hex_num_t *convert_to_hex(char * stringNum){

	int len = strlen(stringNum);
	int hexLen = len % 2 == 0 ? len/2 : len/2 + 1;

	unsigned char a,b;

	hex_num_t *hexNum = hex_init(hexLen);
	unsigned char *start = hexNum->num;

	for(int i=0; i<len-1; i+=2){

		a = ascii_to_hex(stringNum[i]);
		b = ascii_to_hex(stringNum[i+1]);

		a = a << 4;
		*start = a+b;

		start++;
	}

	if (len % 2 != 0){
		a = ascii_to_hex(stringNum[len-1]);
		a = a << 4;
		*start = a;
	}
	return hexNum;

}

unsigned char ascii_to_base64(char a){

	unsigned char base64 = a;

	if ((base64 > UPPERCASE_LOW_BOUND) && (base64 < UPPERCASE_HIGH_BOUND))
		return base64 - UPPERCASE_BASE64_OFFSET;
	else if ((base64 > LOWERCASE_LOW_BOUND) && (base64 < LOWERCASE_HIGH_BOUND))
		return base64 - LOWERCASE_BASE64_OFFSET;
	else if (base64 > DIGIT_LOW && base64 < DIGIT_HIGH)
		return base64 + DIGIT_BASE64_OFFSET;
	else if (base64 == '+')
		return 62;
	else if (base64 == '/')
		return 63;
	else if (base64 == '=')
		return 64;
	else {
		printf("Invalid base 64 character: %c   Exiting...\n", base64);
		exit(0);
	}


}

base_64_t *convert_to_base64(char *buffer){

	int len = strlen(buffer);

	short padding;
	if (buffer[len-2]== '=')
		padding = 2;
	else if (buffer[len-1]=='=')
		padding = 1;
	else
		padding = 0;

	base_64_t *base64 = base64_init(len, padding);
	unsigned char *start = base64->num;
	
	for (int i=0; i<len; i++){
		*start++ = ascii_to_base64(buffer[i]);
	}

	return base64;
	
}

void print_hex(char *msg, hex_num_t *hex){

	printf("%s", msg);
	for (int i=0; i<hex->size; i++)
        printf("%x", hex->num[i]);

    printf("\n");

}

void print_base64(char *msg, base_64_t *base64){

	printf("%s", msg);
	for (int i=0; i<base64->size; i++){
		char c = base64_dic[base64->num[i]];
        printf("%c", base64_dic[base64->num[i]]);
	}
    printf("\n");

}

void free_hex_num(hex_num_t *hex){

	free(hex->num);
	free(hex);

}

void free_base64(base_64_t *base64){

	free(base64->num);
	free(base64);

}
