
#include "../core/dynmem.h"

#define print_free_mem() printf("[ free mem: %i ]\n", (int)dynmem_avail())


static void test_dynmem_init(void)
{
	static unsigned char buf1[256];
	static unsigned char buf2[256];
	static unsigned char buf3[256];

	dynmem_init(buf1, 256);
	dynmem_append(buf2, 256);
	dynmem_append(buf3, 256);
}

static void test_dynmem(void)
{
	print_free_mem();
	char *test1 = dynmem_alloc(64);
	print_free_mem();
	char *test2 = dynmem_alloc(64);
	print_free_mem();

	strcpy(test1, "11111111");
	strcpy(test2, "2222222222222");

	puts(test1);
	puts(test2);

	dynmem_free(test1);
	print_free_mem();
	
	char *test3 = dynmem_alloc(100);
	print_free_mem();

	strcpy(test3, "333");
	puts(test2);
	puts(test3);

	dynmem_free(test3);
	dynmem_free(test2);

	if((test1 = dynmem_alloc(248))) {
		puts("success");
		dynmem_free(test1);
	}

	test1 = dynmem_alloc(60);
	test2 = dynmem_alloc(60);
	test3 = dynmem_alloc(60);
	dynmem_free(test2);
	test2 = dynmem_alloc(72);
	dynmem_free(dynmem_alloc(130));
	dynmem_free(test3);
	dynmem_free(test1);
	dynmem_free(test2);

	print_free_mem();
}
