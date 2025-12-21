#include "utils.h"

char **split_lines(char *s)
{
    char    **res;
    int     start;
    int     lines;
    int     i;
	int		j;

    i = 0;
	j = 0;
    start = 0;
    lines = count_char(s, '\n');
    res = allocate_memory(sizeof(char *) * (lines + 2));
    while (true)
    {
        if (s[j] == '\n' || s[j] == '\0')
        {
            res[i++] = ft_strndup(s + start, j - start);
            start = j + 1;
        }
        if (s[j] == '\0')
            break;
		j++;
    }
    res[i] = NULL;
    return (res);
}
