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

int render_frame(t_maze *maze)
{
    // render_background(maze, 0x202020);

    draw_floor_ceiling(maze);

    raycasting(maze);

    draw_minimap(maze);

    mlx_put_image_to_window(maze->mlx, maze->win, maze->img.img, 0, 0);
    // mlx_destroy_image(maze->mlx, maze->img.img);
    return (0);
}
