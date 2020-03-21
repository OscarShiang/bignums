#ifndef BIG_NUM_H
#define BIG_NUM_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _bn {
    uint32_t *data;
    uint32_t size;
    bool neg;
} bn;

void bn_init(bn *a);
void bn_free(bn *a);
void bn_assign(bn *out, const uint32_t in);

void bn_add(bn *out, const bn *a, const bn *b);  // out = a + b
void bn_sub(bn *out, const bn *a, const bn *b);  // out = a - b
void bn_mul(bn *out, const bn *a, const bn *b);  // out = a * b

void bn_print(bn *out, const uint32_t base);

#endif /* BIG_NUM_H */
