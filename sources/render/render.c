#include "cub3d.h"

void draw_floor_ceiling(t_maze *m)
{
    int y = 0;
    int x;
    int color;

    while (y < m->win_h)
    {
        color = (y < m->win_h / 2) ? m->env.ceiling : m->env.floor;

        x = 0;
        while (x < m->win_w)
        {
            put_pixel(&m->img, x, y, color);
            x++;
        }
        y++;
    }
}

void	draw_minimap_compass(t_maze *m)
{
	mlx_string_put(m->mlx, m->win,
		MM_PADDING + MM_RADIUS - 4,
		MM_PADDING + 2,
		MM_TEXT_COLOR,
		"N");
	mlx_string_put(m->mlx, m->win,
		MM_PADDING + MM_RADIUS - 3,
		MM_PADDING + 6 + MM_RADIUS * 2,
		MM_TEXT_COLOR,
		"S");
	mlx_string_put(m->mlx, m->win,
		MM_PADDING - 4,
		MM_PADDING + MM_RADIUS + 2,
		MM_TEXT_COLOR,
		"W");
	mlx_string_put(m->mlx, m->win,
		MM_PADDING - 2 + MM_RADIUS * 2,
		MM_PADDING + MM_RADIUS + 3,
		MM_TEXT_COLOR,
		"E");
}

int render_frame(t_maze *maze)
{
    // render_background(maze, 0x202020);

    draw_floor_ceiling(maze);

    raycasting(maze);

    render_minimap(maze);

    mlx_put_image_to_window(maze->mlx, maze->win, maze->img.img, 0, 0);

    draw_minimap_compass(maze);
    
    // mlx_destroy_image(maze->mlx, maze->img.img); // where to call
    return (0);
}
