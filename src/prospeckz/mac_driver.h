
#ifndef MACDRIVER_H
#define MACDRIVER_H

#include "xlowpan.h"

/* callback function */
extern void (*xlowpan_receive_pkt)(void *data, size_t length);

/* API */
struct mac_driver *mac_getdrv(void);
void mac_initradio(void);
unsigned char mac_radiohandler(void);

#endif
