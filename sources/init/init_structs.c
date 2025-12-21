#include "cub3d.h"

void init_env(t_env *env)
{
    env->no = NULL;
    env->so = NULL;
    env->we = NULL;
    env->ea = NULL;
    env->floor = -1;
    env->ceiling = -1;
}

void init_img(t_img *img)
{
    t_maze maze = **maze_struct();

    img->img = NULL;
    img->addr = NULL;
    img->bpp = 0;
    img->line_len = 0;
    img->endian = 0;
    img->width = maze.win_w;
    img->height = maze.win_h;
}

void init_map(t_map *map)
{
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
    ft_memset(&map->player, 0, sizeof(t_player));
}
