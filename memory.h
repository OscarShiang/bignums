#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdint.h>
#include <stdlib.h>

static inline void *xmalloc(size_t size)
{
    return malloc(size);
}

static inline void *xrealloc(void *ptr, size_t size)
{
    return realloc(ptr, size);
}

static inline void xfree(void *ptr)
{
    free(ptr);
}

#define MALLOC(s) xmalloc(s)
#define REALLOC(p, s) xrealloc(p, s)
#define FREE(p) xfree(p)

#endif /* _MEMORY_H_ */
