
#include "../support/base64.h"

#define MSG "Hello!123456"
#define MSG_SIZE 13

void test_base64(void)
{
	char str1[BASE64_CALC_ENCODED_SIZE(MSG_SIZE)];
    char str2[MSG_SIZE];

    memset(str1, 'x', sizeof(str1));
    memset(str2, 'x', sizeof(str2));

    base64_encode(str1, (unsigned char*)MSG, MSG_SIZE);

    printf("Encoded: %s\n", str1);

    size_t len = base64_decode((unsigned char*)str2, str1, MSG_SIZE);

    printf("Decoded: %s size=%i %i\n", str2, (int)strlen(str2), (int)len);
}
