#include "cub3d.h"

void	destroy_maze(void)
{
	int	    i;
    t_maze  *maze;

    maze = *maze_struct();
	if (!maze)
		return ;
	if (maze->mlx)
	{
		if (maze->img.img)
			mlx_destroy_image(maze->mlx, maze->img.img);
		i = 0;
		while (i < 4)
		{
			if (maze->tex[i].img)
				mlx_destroy_image(maze->mlx, maze->tex[i].img);
			i++;
		}
		if (maze->win)
			mlx_destroy_window(maze->mlx, maze->win);
		mlx_destroy_display(maze->mlx);
		free(maze->mlx);
	}
}
