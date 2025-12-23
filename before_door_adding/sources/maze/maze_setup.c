#include <cub3d.h>

bool maze_setup()
{
    t_maze *maze;

    maze = *maze_struct();
    maze->mlx = mlx_init();
    if (!maze->mlx)
        error_exit("MLX initialization failed");
    maze->win = mlx_new_window(maze->mlx, 
                            maze->win_w, 
                            maze->win_h, 
                            "ETERNAL MAZE"); // is cub3d name mandatory?
    if (!maze->win)
        error_exit("window creation failed");
    maze->img.img = mlx_new_image(maze->mlx, maze->win_w, maze->win_h);
    if (!maze->img.img)
        error_exit("image creation failed");
    maze->img.addr = mlx_get_data_addr(maze->img.img,
                                    &maze->img.bpp,
                                    &maze->img.line_len,
                                    &maze->img.endian); 
    return (load_textures(maze), true);
}
