
#include "stdfcts.h"
#include <stdint.h>

void *ft_memset(void *s, int c, size_t n)
{
    uint8_t *p = (uint8_t *)s;
    uint8_t byte = (uint8_t)c;
    for (size_t i = 0; i < n; ++i)
        p[i] = byte;
    return s;
}
