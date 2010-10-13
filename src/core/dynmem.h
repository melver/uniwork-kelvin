/*
 * dynmem.h
 *
 * Author: Marco Elver <marco.elver AT gmail.com>
 * Date: Mon Oct 11 21:34:18 BST 2010
 */

#ifndef DYNMEM_H
#define DYNMEM_H

#include <stdlib.h>

void dynmem_init(unsigned char *buffer, size_t size);
void dynmem_append(unsigned char *buffer, size_t size);
size_t dynmem_avail(void);
void *dynmem_alloc(size_t buflen);
void dynmem_free(void *ptr);

/* other functions that are not guaranteed to work. */
void m_memcpy(void *dst, void *src, size_t len);

#ifdef OVERRIDE_MALLOC
  #define malloc(_x) dynmem_alloc(_x)
  #define free(_x) dynmem_free(_x)
  #define memcpy(_d, _s, _l) m_memcpy(_d, _s, _l)
#endif

#endif

