#include "cub3d.h"

static void set_values(t_map *map, double dx, double dy, double px, double py) // if not posible set map from maze struct fct 
{
    map->player.dir.x = dx;
    map->player.dir.y = dy;
    map->player.plane.x = px;
    map->player.plane.y = py;
}

static void get_directions(t_map *map, char dir)
{
    if (dir == 'N')
    {
        set_values(map, 0, -1, 0.66, 0);
    }
    else if (dir == 'S')
    {
        set_values(map, 0, 1, -0.66, 0);
    }
    else if (dir == 'E')
    {
        set_values(map, 1, 0, 0, 0.66);
    }
    else if (dir == 'W')
    {
        set_values(map, -1, 0, 0, -0.66);
    }
}

void parse_player(t_map *map)
{
    int x = 0;
    int y = 0;
    int found = 0;
    char dir;

    while (map->grid[y])
    {
        x = 0;
        while (map->grid[y][x])
        {
            dir = map->grid[y][x];
            if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
            {
                if (found)
                    error_exit("Multiple player spawn points");

                map->player.pos.x = x + 0.5;
                map->player.pos.y = y + 0.5;
                get_directions(map, dir);
                map->grid[y][x] = '0';
                found = 1;
            }
            x++;
        }
        y++;
    }
    if (!found)
        error_exit("No player spawn found in map");
}

