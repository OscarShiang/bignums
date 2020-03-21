#include "bign.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "memory.h"

#define DATASIZE sizeof(uint32_t)

void bn_init(bn *a)
{
    a->data = NULL;
    a->size = 0;
    a->neg = false;
}

void bn_assign(bn *out, const uint32_t in)
{
    out->data = MALLOC(DATASIZE);
    out->size = 1;
    out->data[0] = in;
}

void bn_free(bn *a)
{
    if (a->data)
        FREE(a->data);
}

static inline uint32_t max(uint32_t a, uint32_t b)
{
    return (a > b) ? a : b;
}

static void print_bits(uint32_t a) 
{
    for (int i = 31; i >= 0; i--) {
	if (a & (1 << i))
	    printf("1");
	else
	    printf("0");
    }
}

static char *bn_todec(bn *a)
{
    char str[8 * DATASIZE * a->size / 3 + 2];
    unsigned int n[a->size + 1];

    memset(str, '0', sizeof(str) - 1);
    str[sizeof(str) - 1] = '\0';

    memcpy(n, a->data, DATASIZE * a->size);
    for (int i = 0; i < 8 * DATASIZE * a->size; i++) {
        int carry;

        carry = (n[a->size - 1] >= 0x80000000);

        for (int j = a->size - 1; j >= 0; j--)
            n[j] = ((n[j] << 1) & 0xffffffff) +
                   ((j - 1) >= 0 ? (n[j - 1] >= 0x80000000) : 0);

        for (int j = sizeof(str) - 2; j >= 0; j--) {
            str[j] += str[j] - '0' + carry;
            carry = (str[j] > '9');
            if (carry)
                str[j] -= 10;
        }
    }

    // search for numbers
    int i = 0;
    while (i < sizeof(str) - 2 && str[i] == '0')
        i++;

    // passing string back
    char *p = MALLOC(sizeof(str) - i);
    memcpy(p, str + i, sizeof(str) - i);

    return p;
}

void bn_print(bn *out, const uint32_t base)
{
    char *dec;
    switch (base) {
    case 2:
	for (int i = out->size - 1; i >= 0; i--) {
	    print_bits(out->data[i]);
	    printf(" ");
	}
	printf("\n");
        break;

    case 10:
	dec = bn_todec(out);
	printf("%s\n", dec);
	FREE(dec);
        break;
    }
}

void bn_add(bn *out, const bn *a, const bn *b)
{
    uint32_t len = max(a->size, b->size) + 1;
    uint32_t sum[len];
    memset(sum, 0, sizeof(sum));

    uint64_t l = 0;
    for (int i = 0; i < len; i++) {
        uint64_t A = (i < a->size) ? a->data[i] : 0;
        uint64_t B = (i < b->size) ? b->data[i] : 0;
        l += A + B;
        sum[i] = l;
        l >>= 32;
    }

    for (int i = len - 1; i >= 1; i--) {
	if (!sum[i])
	    len--;
	else
	    break;
    }
    if (out->size < len) {
	out->data = REALLOC(out->data, len);
	out->size = len;
    }
    memcpy(out->data, sum, len * DATASIZE);
}
