/*
 * xlowpan.h
 *
 * Author: Marco Elver <marco.elver AT gmail.com>
 * Date: Thu Oct  7 14:29:04 BST 2010
 */

#ifndef XLOWPAN_H
#define XLOWPAN_H

#include <stdlib.h>

/* Definitions */
#define XLOWPAN_DISPATCH_IPV6 0x41 /* 01000001 =  65 */
#define XLOWPAN_DISPATCH_MESH 0x80 /* 1000xxxx = 128, for now just fixed 64bit, no 16bit address support */
#define XLOWPAN_DISPATCH_SLIP 0x77

/* 802.15.4 MAC header takes 25, which leaves us with 127 - 25 bytes */
#define MAC_MAX_PAYLOAD 102

/* Address definition */

struct xlowpan_addr64 {
	unsigned char addr[8];
};

#define XLOWPAN_ADDR_LEN	8

extern struct xlowpan_addr64 XLOWPAN_ADDR_BCAST;

#define XLOWPAN_SET_ADDR64(aX, a0, a1, a2, a3, a4, a5, a6, a7) \
	(aX).addr[0]=a0; (aX).addr[1]=a1; (aX).addr[2]=a2; (aX).addr[3]=a3; \
	(aX).addr[4]=a4; (aX).addr[5]=a5; (aX).addr[6]=a6; (aX).addr[7]=a7;

#if 0
/*
 * Header definitions
 * ------------------
 * Do not copy them to the packet buffer directly, due to padding issues.
 * These are just here for reference.
 */

struct xlowpan_header_mesh {
	unsigned char dsp; /* dispatch */
	struct xlowpan_addr64 org_addr;
	struct xlowpan_addr64 fin_addr;
};

struct xlowpan_header_slip {
	unsigned char dsp; /* dispatch */
	unsigned char length;

	unsigned char session; /* random number, unique until seq gets reset. */
	unsigned char seq;

	void *data;
};
#endif

/* mac driver */

struct mac_driver {
	void (*send_pkt)(void *data, size_t length);
	void (*set_receive_pkt)(void (*receive_pkt)(void *data, size_t length));
	void (*get_addr64)(struct xlowpan_addr64 *addr); /* return 64bit address; should be HW-id based. */
	unsigned char (*make_session)(void); /* should return a random number */
};

/* API */

void xlowpan_init(struct mac_driver *driver);
void xlowpan_shutdown(void);
size_t xlowpan_send(struct xlowpan_addr64 *dstaddr, void* data, size_t length);
size_t xlowpan_recv(struct xlowpan_addr64 *srcaddr, void *data, size_t buflen);
void xlowpan_addrcpy(struct xlowpan_addr64 *dst, struct xlowpan_addr64 *src);
int xlowpan_addrcmp(struct xlowpan_addr64 *addr1, struct xlowpan_addr64 *addr2);
struct xlowpan_addr64 *xlowpan_getaddr(void);

#endif /* XLOWPAN_H */
