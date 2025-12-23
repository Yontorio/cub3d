#include "cub3d.h"

void check_map_chars(t_map *map)
{
    int x;
    int y = 0;
    char c;

    while (map->grid[y])
    {
        x = 0;
        while (map->grid[y][x])
        {
            c = map->grid[y][x];
            if (c != '0' && c != '1' &&
                c != 'D' && c != 'd' &&
                c != 'N' && c != ' ' &&
                c != 'S' && c != 'E' && c != 'W')
                error_exit("Invalid character in map");
            x++;
        }
        y++;
    }
}


char	**duplicate_map(t_map *map)
{
	char	**copy;
	char	**grid;
	int		j;

	j = -1;
	grid = map->grid;
	copy = allocate_memory((map->height + 1) * sizeof(char *));
	while (grid[++j])
		copy[j] = ft_strdup(grid[j]);
	copy[j] = NULL;
	return (copy);
}

void flood_fill(char **map, int y, int x)
{
    if (y < 0 || x < 0 || !map[y] || !map[y][x] || map[y][x] == ' ')
        error_exit("Map is not fully surrounded by walls");
    if (map[y][x] == '1')
        return;
    map[y][x] = '1';
    flood_fill(map, y + 1, x);
    flood_fill(map, y - 1, x);
    flood_fill(map, y, x + 1);
    flood_fill(map, y, x - 1);
}

void check_flood_result(char **copy)
{
    int y;
    int x;

    y = 0;
    while (copy[y])
    {
        x = 0;
        while (copy[y][x])
        {
            if (copy[y][x] != '1' && copy[y][x] != ' ')
                flood_fill(copy, y, x);
            x++;
        }
        y++;
    }
}

void check_map_closed(t_map *map)
{
    char **copy;

    set_current_section(TEMPORARY);
    copy = duplicate_map(map);
    set_current_section(REMAINS);
    flood_fill(copy, map->player.pos.y, map->player.pos.x);
    check_flood_result(copy);
	destroy_section(TEMPORARY);
}
