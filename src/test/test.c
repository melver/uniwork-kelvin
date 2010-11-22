
/* include up here to test bare includes */
#include "../core/dynmem.h"
#include "../core/hashmap.h"
#include "../core/xlowpan.h"
#include "../support/base64.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void separate(const char *info)
{
	if(info)
		printf("------- %s -------\n", info);
	else
		puts(  "------------------");
}

static void section(const char* section)
{
	printf("\n====== %s =======\n\n", section);
}

#include "test_base64.h"
#include "test_dynmem.h"
#include "test_hashmap.h"
#include "test_xlowpan.h"

int main(int argc, char* argv[])
{
	int i;

	section("base64");
	test_base64();

	section("dynmem");
	test_dynmem_init();
	for(i=0; i<3; ++i) {
		separate(NULL);
		test_dynmem();
	}

	section("hashmap");
	test_hashmap();

	section("xlowpan");
	test_xlowpan();
	
	return 0;
}

