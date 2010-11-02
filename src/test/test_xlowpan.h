
#include <time.h>

#include "../core/xlowpan.h"

static void (*receive_pkt)(void *data, size_t length);
static void send_pkt(void *data, size_t length)
{
	printf("data: %s; length: %i\n", (char*)data, (int)length);

	xlowpan_getaddr()->addr[0] = 'h';
	receive_pkt(data, length);
}

static void set_receive_pkt(void (*_receive_pkt)(void *data, size_t length))
{
	puts("called set_receive_pkt");
	receive_pkt = _receive_pkt;
}

static void get_addr64(struct  xlowpan_addr64 *addr)
{
	puts("called get_addr64");
	XLOWPAN_SET_ADDR64((*addr), 'h', 'e', 'l', 'l', 'o', '!', '!', 0);
}

unsigned char make_session(void)
{
	puts("called make_session");
	return (unsigned char)(rand() % 0xff);
}

void mac_init(void)
{
	puts("called mac_init");
}

static void test_xlowpan(void)
{
	srand(time(NULL));

	printf("random session: %i\n", make_session());
	printf("random session: %i\n", make_session());

	struct mac_driver driver = {
		send_pkt,
		set_receive_pkt,
		get_addr64,
		make_session,
		mac_init
	};

	separate("xlowpan init");
	xlowpan_init(&driver);

	const char *some_data = "my name is dilbert. :)";
	enum xlowpan_addr_type dst_type;

	/* only 1 send */
	xlowpan_send(xlowpan_getaddr(), (void*)some_data, strlen(some_data)+1);

	struct xlowpan_addr64 other_addr = {
		"other.."
	};

	/* should have 1 send */
	xlowpan_send(&other_addr, (void*)some_data, strlen(some_data)+1);

	xlowpan_getaddr()->addr[0] = 'x'; /* testing forwarding, faking sender */
	xlowpan_send(&XLOWPAN_ADDR_BCAST, (void*)some_data, strlen(some_data)+1);

	char buf[MAC_MAX_PAYLOAD];
	while(xlowpan_recv4(NULL, &dst_type, buf, MAC_MAX_PAYLOAD)) {
		printf("dst_type=%s, buf=%s\n", (dst_type == XLOWPAN_ADDR_TYPE_NULL ? "NULL" :
										 dst_type == XLOWPAN_ADDR_TYPE_IGNORE ? "IGNORE" :
										 dst_type == XLOWPAN_ADDR_TYPE_BCAST ? "BCAST" :
										 dst_type == XLOWPAN_ADDR_TYPE_SELF ? "SELF" : "UNKNOWN") , buf);
	}

	xlowpan_shutdown();
}
