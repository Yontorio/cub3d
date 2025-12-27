#include "utils.h"

char **split_one_time(char *str)
{
    char    **parts;
    int     start;
    int     i;
    
    parts = allocate_memory(sizeof(char *) * 3);
    ft_memset(parts, 0, sizeof(char *) * 3);
    i = skip_spaces(str, 0);
    start = i;
    while (str[i] && str[i] != ' ')
        i++;
    parts[0] = ft_substr(str, start, i - start);
    i += skip_spaces(str, i);
    if (str[i])
        parts[1] = ft_strdup(str + i);
    return (parts);
}