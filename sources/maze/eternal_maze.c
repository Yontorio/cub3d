#include <cub3d.h>

// int eternal_maze()
// {
//     t_maze *maze;

//     maze = *maze_struct();

//     mlx_loop_hook(maze->mlx, render_all, maze);

//     mlx_hook(maze->win, 2, 0, key_handler, maze);
//     mlx_hook(maze->win, 17, 0, close_window, NULL);

//     mlx_loop(maze->mlx);
//     return 0;
// }

int eternal_maze(void)
{
    t_maze *maze;

    maze = *maze_struct();

    mlx_hook(maze->win, 2, 1L << 0, key_press, maze);
    mlx_hook(maze->win, 3, 1L << 1, key_release, maze);
    mlx_hook(maze->win, 17, 0, close_window, maze);

    mlx_loop_hook(maze->mlx, update_player, maze);
    

    mlx_loop(maze->mlx);
    return (0);
}

