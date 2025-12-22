#include "cub3d.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    t_maze *maze = *maze_struct();

    if (x < 0 || x >= img->width || y < 0 || y >= img->height) // is the last condition necessery
        return;

    char *px = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)px = color;
}

static int	inside_circle(t_mm mm, int x, int y)
{
	int	dx;
	int	dy;

	dx = x - mm.cx;
	dy = y - mm.cy;
	return (dx * dx + dy * dy <= mm.radius * mm.radius);
}

void draw_player(t_img *img, t_mm mm)
{
    int x;
    int y;
    int radius;
    int color;

    color = MM_PLAYER_COLOR;
    radius = MM_PLAYER_RADIUS;
    y = -radius;
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if (x * x + y * y <= radius * radius)
                put_pixel(img, mm.cx + x, mm.cy + y, color);
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
static void	rotate(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = old_x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	draw_circle_border(t_img *img, t_mm mm)
{
	int	x;
	int	y;
	int	dist_sq;
	int	inner_sq;

	y = -(mm.radius += 10);
    inner_sq = ((mm.radius - MM_BR_THICk) * (mm.radius - MM_BR_THICk));
	while (y <= mm.radius)
	{
		x = -mm.radius;
		while (x <= mm.radius)
		{
			dist_sq = x * x + y * y;
			if (dist_sq <= (mm.radius * mm.radius))
			{
				if (dist_sq >= inner_sq)
					put_pixel(img, mm.cx + x, mm.cy + y, MM_BR_COLOR);
				else
					put_pixel(img, mm.cx + x, mm.cy + y, MM_BG_COLOR);
			}
			x++;
		}
		y++;
	}
}

static void	draw_square_clipped(t_img *img, t_mm mm, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MM_TILE)
	{
		x = 0;
		while (x < MM_TILE)
		{
			if (inside_circle(mm, mm.sx + x, mm.sy + y))
				put_pixel(img, mm.sx + x, mm.sy + y, color);
			x++;
		}
		y++;
	}
}

void	draw_fov(t_player *p, t_img *img, t_mm mm)
{
	double		lx;
	double		ly;
	double		rx;
	double		ry;
	int			i;

	i = 0;
	lx = p->dir.x;
	ly = p->dir.y;
	rx = p->dir.x;
	ry = p->dir.y;
	rotate(&lx, &ly, FOV_ANGLE / 2);
	rotate(&rx, &ry, -FOV_ANGLE / 2);
	while (i < mm.radius)
	{
		if (inside_circle(mm, mm.cx + lx * i, mm.cy + ly * i))
			put_pixel(img, mm.cx + lx * i, mm.cy + ly * i, MM_PLAYER_COLOR);
		if (inside_circle(mm, mm.cx + rx * i, mm.cy + ry * i))
			put_pixel(img, mm.cx + rx * i, mm.cy + ry * i, MM_PLAYER_COLOR);
		i++;
	}
}

void	draw_rounded_map(t_maze *maze, t_mm mm)
{
	int	x;
	int	y;

	y = 0;
	while (y < maze->map.height)
	{
		x = 0;
		while (x < maze->map.width)
		{
			mm.sx = mm.cx + (x - maze->map.player.pos.x) * MM_TILE;
			mm.sy = mm.cy + (y - maze->map.player.pos.y) * MM_TILE;
			if (inside_circle(mm, mm.sx, mm.sy))
			{
				if (maze->map.grid[y][x] == '1')
					draw_square_clipped(&maze->img, mm, 0x222222);
				else
					draw_square_clipped(&maze->img, mm, 0x888888);
			}
			x++;
		}
		y++;
	}
}



static t_mm	set_minimap_struct(void)
{
	t_mm	minimap;

	minimap.cx = MM_PADDING + MM_RADIUS;
	minimap.cy = MM_PADDING + MM_RADIUS;
	minimap.radius = MM_RADIUS;
    minimap.height = 0;
    minimap.width = 0;
    minimap.sx = 0;
    minimap.sy = 0;
	return (minimap);
}
void render_minimap(t_maze *maze)
{
    t_mm        minimap;
    t_player   *player;
    t_img       *img;

    img = &maze->img;
    player = &maze->map.player;
    minimap = set_minimap_struct();
    draw_circle_border(img, minimap);
    draw_rounded_map(maze, minimap);
    draw_player(img, minimap);
    draw_fov(player, img, minimap);
}
