
#include "../core/hashmap.h"

#define HASH_BUCKETS 16

static struct ll_node *print_node(struct ll_node *node, void *param)
{
	puts((const char*)node->data);
	if(param) {
		if(!strcmp((const char*)node->data, (const char*)param)) {
			return node;
		}
	}

	return NULL;
}

static void destroy_node(struct ll_node *node, void *param)
{
	print_node(node, param);
}

static size_t simple_hash(void *_key)
{
	const char *key = (const char*)_key;
	size_t hash = 0;

	while(*key) {
		hash += *key++;
	}

	printf("hash for '%s' is %i, bucket=%i\n", (char*)_key, (int)hash, (int)hash%HASH_BUCKETS);

	return hash;
}

static void test_hashmap(void)
{
	struct linked_list *list;
	struct ll_node *node;

	list = llist_create();

	node = llist_append(list);
	node->data = (void*)"1";
	llist_append(list)->data = (void*)"2";
	llist_append(list)->data = (void*)"3";
	llist_append(list)->data = (void*)"4";
	llist_append(list)->data = (void*)"5";

	separate("searching list with print_node");
	llist_search(list, print_node, NULL);

	separate("removing 1");
	llist_remove(list, node, destroy_node, NULL);

	separate("searching list and removing 3");
	node = llist_search(list, print_node, (void*)"3");
	llist_remove(list, node, NULL, NULL);

	separate("appending foo and destroying");
	llist_append(list)->data = (void*)"foo";
	llist_destroy(list, destroy_node, NULL);


	separate("HASH MAPS");

	struct hash_map *map;

	map = hmap_create(HASH_BUCKETS, simple_hash);
	hmap_set(map, "1", "hi there");
	hmap_set(map, "Y", "bar");
	hmap_set(map, "foo", "baz");
#define puts(msg) puts((msg ? msg : "memerr"))
	puts((const char*)hmap_get(map, "1"));
	puts((const char*)hmap_get(map, "Y"));
	puts((const char*)hmap_get(map, "foo"));
#undef puts

	hmap_destroy(map, NULL);
}

