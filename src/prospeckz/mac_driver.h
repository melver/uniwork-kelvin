
#include "xlowpan.h"

extern void (*xlowpan_receive_pkt)(void *data, size_t length);
struct mac_driver *mac_getdrv(void);