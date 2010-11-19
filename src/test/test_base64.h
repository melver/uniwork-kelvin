
#include "../support/base64.h"

#define MSG "Hello!12345612356"
#define MSG_SIZE 19 // with \0

void test_base64(void)
{
	char str1[BASE64_CALC_ENCODED_SIZE(MSG_SIZE)+1];
    char str2[MSG_SIZE];

    memset(str1, 'x', sizeof(str1));
    memset(str2, 'x', sizeof(str2));

    size_t len_enc = base64_encode(str1, (unsigned char*)MSG, MSG_SIZE);

    printf("Encoded: %s len_enc=%i macro_encoded_size=%i\n", str1, (int)len_enc, BASE64_CALC_ENCODED_SIZE(MSG_SIZE));

    size_t len_dec = base64_decode((unsigned char*)str2, str1, MSG_SIZE);

    printf("Decoded: %s strlen=%i len_dec=%i macro_decode_size=%i\n", str2, (int)strlen(str2), (int)len_dec, (int)BASE64_CALC_DECODED_SIZE(len_enc));
}
