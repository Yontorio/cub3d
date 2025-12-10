#include "cub3d.h"

bool init_maze(t_maze **pointer)
{
    t_maze *maze;

    *pointer = allocate_memory(sizeof(t_maze));
    maze = *pointer;
    maze->mlx = NULL;
    maze->win = NULL;
    maze->win_w = 1280;
    maze->win_h = 720;
    init_img(&maze->img);
    init_env(&maze->env);
    init_map(&maze->map);
    return (true);
}
