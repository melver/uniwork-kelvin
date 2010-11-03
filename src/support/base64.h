/*
 * Copyright (C), 2000-2007 by the monit project group.
 * All Rights Reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/**
 * Marco: Modified to work with an embedded system.
 * Removed dependencies on malloc and string functions.
 */

#ifndef BASE64_H
#define BASE64_H

#include <stdlib.h>

/**
 * Calculates the size of a string after encoding a packet of size _buflen.
 * With a proper C compiler this can be used in array declarations,
 * when using fixed length packets.
 */
#define BASE64_CALC_ENCODED_SIZE(_buflen) ((((_buflen)*4)/3)+4)

/**
 * Calculates the size of a buffer after decoding a string of length ___strlen.
 */
#define BASE64_CALC_DECODED_SIZE(___strlen) ((((___strlen)-2)*3)/4)

/**
 * Base64 encode and return size data in 'src'. The caller must free the
 * returned string.
 * @param dst buffer to be used to store result.
 * @param src The data to be base64 encode
 * @param size The size of the data in src
 * @return encoded string otherwise NULL. Points to dst if successful.
 */
char *base64_encode(char *dst, unsigned char *src, size_t size);

/**
 * Decode the base64 encoded string 'src' into the memory pointed to by
 * 'dest'.
 * @param dest Pointer to memory for holding the decoded string.
 * Must be large enough to recieve the decoded string.
 * @param src A base64 encoded string.
 * @return the length of the decoded string. Length 0 if failed.
 */
size_t base64_decode(unsigned char *dest, char *src);

#endif
