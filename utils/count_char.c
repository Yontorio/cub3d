#include "utils.h"

int count_char(const char *s, char c)
{
    int count;

    count = 0;
    if (!s)
        return (0);
    while (*s)
    {
        if (*s == c)
            count++;
        s++;
    }
    return (count);
}