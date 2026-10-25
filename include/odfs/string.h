/*
 * string.h - small string helpers
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef ODFS_STRING_H
#define ODFS_STRING_H

static inline unsigned char odfs_ascii_tolower(unsigned char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return (unsigned char)(ch + ('a' - 'A'));
    return ch;
}

/*
 * Hash of the name folded the way odfs_strcasecmp() folds it. Rotate
 * and xor rather than a multiplicative hash: GCC turns any multiply,
 * even one written as shifts, into a libgcc call per character on the
 * 68000. The final shifts mix the leading characters into the low bits
 * that pick a hash bucket.
 */
static inline unsigned int odfs_strcasehash(const char *s)
{
    unsigned int hash = 0;

    while (*s) {
        hash = (hash << 5) | (hash >> 27);
        hash ^= odfs_ascii_tolower((unsigned char)*s++);
    }
    hash ^= hash >> 16;
    hash ^= hash >> 8;
    return hash;
}

static inline int odfs_strcasecmp(const char *a, const char *b)
{
    unsigned char ca;
    unsigned char cb;

    for (;;) {
        ca = odfs_ascii_tolower((unsigned char)*a++);
        cb = odfs_ascii_tolower((unsigned char)*b++);
        if (ca != cb || ca == '\0')
            return (int)ca - (int)cb;
    }
}

#endif /* ODFS_STRING_H */
