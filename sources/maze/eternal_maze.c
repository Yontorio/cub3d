#include <cub3d.h>

int eternal_maze()
{
    t_maze *maze;

    maze = *maze_struct();

    mlx_loop_hook(maze->mlx, render_all, maze);

    mlx_hook(maze->win, 2, 1, key_handler, maze);
    mlx_hook(maze->win, 17, 0, close_window, NULL);

    mlx_loop(maze->mlx);
    return 0;
}
