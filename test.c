#include <stdio.h>
#include <stdlib.h>

#include "bign.h"

#define autofree __attribute__((cleanup(bn_free)))

int main(void)
{
    autofree bn out, a, b;
    bn_init(&a);
    bn_init(&b);
    bn_init(&out);

    bn_assign(&a, 100);
    bn_assign(&b, 200);

    bn_add(&out, &a, &b);

    bn_print(&out, 10);

    return 0;
}
