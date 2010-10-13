
#include "../core/dynmem.h"

static void test_dynmem(void)
{
	static unsigned char buf1[256];
	static unsigned char buf2[256];
	static unsigned char buf3[256];
	static unsigned char buf4[256];

	dynmem_init(buf1, 256);
	dynmem_append(buf2, 256);
	dynmem_append(buf3, 256);
	dynmem_append(buf4, 256);

	printf("free mem: %i\n", (int)dynmem_avail());
	char *test1 = dynmem_alloc(64);
	printf("free mem: %i\n", (int)dynmem_avail());
	char *test2 = dynmem_alloc(64);
	printf("free mem: %i\n", (int)dynmem_avail());

	strcpy(test1, "11111111");
	strcpy(test2, "2222222222222");

	puts(test1);
	puts(test2);

	dynmem_free(test1);
	printf("free mem: %i\n", (int)dynmem_avail());

	char *test3 = dynmem_alloc(100);
	printf("free mem: %i\n", (int)dynmem_avail());

	strcpy(test3, "333");
	puts(test2);
	puts(test3);

	dynmem_free(test3);
	dynmem_free(test2);

	if((test1 = dynmem_alloc(248))) {
		puts("success");
		dynmem_free(test1);
	}

	printf("free mem: %i\n", (int)dynmem_avail());
}
