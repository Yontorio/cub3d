#include "cub3d.h"

static int count_lines(char **lines)
{
    int count = 0;
    while (lines[count])
        count++;
    return count;
}

int get_max_width(char **map)
{
    int i = 0, max = 0;
    while (map[i])
    {
        int len = ft_strlen(map[i]);
        if (len > max)
            max = len;
        i++;
    }
    return max;
}

int is_map_line(char *line)
{
    int i;

    i = skip_spaces(line, 0);
    return (line[i] == '1' || line[i] == '0');
}


// void normalize_map(t_map *map)
// {
//     int max = map->width;
//     int i;

//     for (i = 0; map->grid[i]; i++)
//     {
//         int len = ft_strlen(map->grid[i]);

//         if (len < max)
//         {
//             char *new_line = ft_realloc(map->grid[i], len + 1, max + 1);

//             ft_memset(new_line + len, ' ', max - len);

//             new_line[max] = '\0';

//             map->grid[i] = new_line;
//         }
//     }
// }

void extract_map(char **lines)
{
    int i, map_lines;
    char **grid;
    t_map *map;

    i = -1;
    map = &((*maze_struct())->map);
    map_lines = count_lines(lines);
    grid = allocate_memory(sizeof(char *) * (map_lines + 1));
    while ((++i) < map_lines)
        grid[i] = ft_strdup(lines[i]);
    grid[map_lines] = NULL;
    map->grid = grid;
    map->height = map_lines;
    map->width = get_max_width(map->grid); // if no minimap rm it
	parse_player(map);
    // normalize_map(map); // is it necess?
    check_map_chars(map);
    check_map_closed(map);
}
