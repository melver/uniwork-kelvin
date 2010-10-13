
#include "PRS8.h"
#include "prospeckz_radio.h"
#include "serial.h"

#include "mac_driver.h"

#define HW_ADDR	3

void (*xlowpan_receive_pkt)(void *data, size_t length);

static void send_pkt(void *data, size_t length)
{
	//serial_cprint("send_pkt: sending packet");
	Radio_transmit((unsigned char*)data, (unsigned char)length);
	//serial_cprint("send_pkt: sending done");
}

static void set_receive_pkt(void (*receive_pkt)(void *data, size_t length))
{
	serial_cprint("called set_receive_pkt");
	xlowpan_receive_pkt = receive_pkt;
}

/* return 64bit address; should be HW-id based. */
static void get_addr64(struct xlowpan_addr64 *addr)
{
	unsigned char hw_addr = HW_ADDR;//Radio_getHWAddr();
	serial_cprint("called get_addr64");
	XLOWPAN_SET_ADDR64((*addr), 'S', 'L', 'I', 'P', 'C', 'C', hw_addr, hw_addr);
}

/* should return a random number. TODO: needs proper random! */
static unsigned char make_session(void)
{
	static unsigned char sess = 0;
	unsigned char newsess;
	serial_cprint("called make_session");
	
	do {
		newsess = PRS8_bReadPRS();
	} while(newsess == sess);
	sess = newsess;
	
	return sess;
}

struct mac_driver *mac_getdrv(void)
{
	static struct mac_driver drv;
	serial_cprint("called mac_getdrv");
	
	drv.send_pkt = send_pkt;
	drv.set_receive_pkt = set_receive_pkt;
	drv.get_addr64 = get_addr64;
	drv.make_session = make_session;
	
	return &drv;
}