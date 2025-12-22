#include "cub3d.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    t_maze *maze = *maze_struct();

    if (x < 0 || x >= img->width || y < 0 || y >= img->height) // is the last condition necessery
        return;

    char *px = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)px = color;
}
static int inside_circle(int cx, int cy, int x, int y, int r)
{
    int dx = x - cx;
    int dy = y - cy;
    return (dx * dx + dy * dy <= r * r);
}
void draw_square_clipped(
    t_img *img,
    int sx,
    int sy,
    int size,
    int color,
    int cx,
    int cy,
    int radius)
{
    int x;
    int y;

    y = 0;
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            if (inside_circle(cx, cy, sx + x, sy + y, radius))
                put_pixel(img, sx + x, sy + y, color);
            x++;
        }
        y++;
    }
}

void draw_player_dir(t_img *img, int x, int y, t_player *p)
{
    int i = 0;

    while (i < 12)
    {
        put_pixel(img,
            x + p->dir.x * i,
            y + p->dir.y * i,
            0xFF0000);
        i++;
    }
}

void draw_circle(t_img *img, int cx, int cy, int r, int color)
{
    int x;
    int y;

    y = -r;
    while (y <= r)
    {
        x = -r;
        while (x <= r)
        {
            if (x * x + y * y <= r * r)
                put_pixel(img, cx + x, cy + y, color);
            x++;
        }
        y++;
    }
}


void draw_square(t_img *img, int sx, int sy, int size, int color)
{
    int y = 0;
    int x;

    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            put_pixel(img, sx + x, sy + y, color);
            x++;
        }
        y++;
    }
}
static void rotate(double *x, double *y, double angle)
{
    double old_x = *x;
    *x = old_x * cos(angle) - *y * sin(angle);
    *y = old_x * sin(angle) + *y * cos(angle);
}

void draw_circle_border(
    t_img *img,
    int cx,
    int cy,
    int radius,
    int border_color
)
{
    int y;
    int x;

    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
        {
            int dist_sq = x * x + y * y;
            int r_sq = radius * radius;
            int inner_sq = (radius - MM_BORDER_THICKNESS)
                            * (radius - MM_BORDER_THICKNESS);

            // outside circle → ignore
            if (dist_sq > r_sq)
                continue;

            // border
            if (dist_sq >= inner_sq)
            {
                put_pixel(img, cx + x, cy + y, border_color);
            }
            // background
            else
            {
                put_pixel(img, cx + x, cy + y, MM_BG_COLOR);
            }
        }
    }
}

void draw_fov(t_maze *m, int cx, int cy)
{
    t_player *p = &m->map.player;

    double lx = p->dir.x;
    double ly = p->dir.y;
    double rx = p->dir.x;
    double ry = p->dir.y;

    rotate(&lx, &ly,  FOV_ANGLE / 2);
    rotate(&rx, &ry, -FOV_ANGLE / 2);

    int i = 0;
    while (i < MM_RADIUS)
    {
        if (inside_circle(cx, cy,
            cx + lx * i,
            cy + ly * i,
            MM_RADIUS))
            put_pixel(&m->img,
                cx + lx * i,
                cy + ly * i,
                0xAD0900);

        if (inside_circle(cx, cy,
            cx + rx * i,
            cy + ry * i,
            MM_RADIUS))
            put_pixel(&m->img,
                cx + rx * i,
                cy + ry * i,
                0xAD0900);
        i++;
    }
}

void draw_minimap(t_maze *m)
{
        draw_circle_border(
        &m->img,
        MM_PADDING + MM_RADIUS,
        MM_PADDING + MM_RADIUS,
        MM_RADIUS + 10,
        0x63120D
    );
    int cx = MM_PADDING + MM_RADIUS;
    int cy = MM_PADDING + MM_RADIUS;

    int x;
    int y;

    y = 0;
    while (y < m->map.height)
    {
        x = 0;
        while (x < m->map.width)
        {
            int draw_x = cx +
                (x - m->map.player.pos.x) * MM_TILE;
            int draw_y = cy +
                (y - m->map.player.pos.y) * MM_TILE;

            if (inside_circle(cx, cy, draw_x, draw_y, MM_RADIUS))
            {
                if (m->map.grid[y][x] == '1')
                    draw_square_clipped(&m->img, draw_x, draw_y,
                        MM_TILE, 0x222222, cx, cy, MM_RADIUS);
                else
                    draw_square_clipped(&m->img, draw_x, draw_y,
                        MM_TILE, 0x888888, cx, cy, MM_RADIUS);
            }
            x++;
        }
        y++;
    }

    // PLAYER
    draw_circle(&m->img, cx, cy, 4, 0xAD0900);
    draw_fov(m, cx, cy);

}


