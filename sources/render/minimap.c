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

void	draw_backgroud_border(t_img *img, t_mm mm)
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
				else if (maze->map.grid[y][x] == 'D')
					draw_square_clipped(&maze->img, mm, 0x6633000);
				else if (maze->map.grid[y][x] == 'd')
					draw_square_clipped(&maze->img, mm,  0x555555);
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
    draw_backgroud_border(img, minimap);
    draw_rounded_map(maze, minimap);
    draw_player(img, minimap);
    draw_fov(player, img, minimap);
}

























// typedef struct s_rect
// {
// 	int	x;
// 	int	y;
// 	int	width;
// 	int	height;
// }	t_rect;

// typedef struct s_circle
// {
// 	int	cx;
// 	int	cy;
// 	int	radius;
// }	t_circle;

// /*
// ** Draws a single pixel to image buffer
// ** @param img: Image structure
// ** @param x: X coordinate
// ** @param y: Y coordinate
// ** @param color: Color in integer format
// */
// void	put_pixel(t_img *img, int x, int y, int color)
// {
// 	char	*pixel;

// 	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
// 		return ;
// 	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
// 	*(unsigned int *)pixel = color;
// }

// /*
// ** Checks if point (x,y) is inside circle
// ** @param cx: Circle center X
// ** @param cy: Circle center Y
// ** @param x: Point X
// ** @param y: Point Y
// ** @param r: Circle radius
// ** @return: 1 if inside, 0 otherwise
// */
// static int	is_inside_circle(int cx, int cy, int x, int y, int r)
// {
// 	int	dx;
// 	int	dy;

// 	dx = x - cx;
// 	dy = y - cy;
// 	return (dx * dx + dy * dy <= r * r);
// }

// /*
// ** Draws filled square clipped to circle boundary
// ** @param img: Image buffer
// ** @param rect: Square rectangle
// ** @param circle: Clipping circle
// ** @param color: Square color
// */
// static void	draw_square_clipped(t_img *img, t_rect rect,
// 	t_circle circle, int color)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < rect.height)
// 	{
// 		x = 0;
// 		while (x < rect.width)
// 		{
// 			if (is_inside_circle(circle.cx, circle.cy,
// 					rect.x + x, rect.y + y, circle.radius))
// 				put_pixel(img, rect.x + x, rect.y + y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// /*
// ** Draws filled circle
// ** @param img: Image buffer
// ** @param circle: Circle parameters
// ** @param color: Circle color
// */
// void	draw_circle(t_img *img, t_circle circle, int color)
// {
// 	int	x;
// 	int	y;
// 	int	r_squared;

// 	r_squared = circle.radius * circle.radius;
// 	y = -circle.radius;
// 	while (y <= circle.radius)
// 	{
// 		x = -circle.radius;
// 		while (x <= circle.radius)
// 		{
// 			if (x * x + y * y <= r_squared)
// 			{
// 				put_pixel(img, circle.cx + x, circle.cy + y, color);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// /*
// ** Draws filled square
// ** @param img: Image buffer
// ** @param rect: Square parameters
// ** @param color: Square color
// */
// void	draw_square(t_img *img, t_rect rect, int color)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < rect.height)
// 	{
// 		x = 0;
// 		while (x < rect.width)
// 		{
// 			put_pixel(img, rect.x + x, rect.y + y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// /*
// ** Rotates vector by given angle
// ** @param x: Pointer to X component
// ** @param y: Pointer to Y component
// ** @param angle: Rotation angle in radians
// */
// static void	rotate_vector(double *x, double *y, double angle)
// {
// 	double	old_x;

// 	old_x = *x;
// 	*x = old_x * cos(angle) - *y * sin(angle);
// 	*y = old_x * sin(angle) + *y * cos(angle);
// }

// /*
// ** Draws circle with colored border
// ** @param img: Image buffer
// ** @param circle: Circle parameters
// ** @param border_color: Border color
// */
// void	draw_circle_border(t_img *img, t_circle circle, int border_color)
// {
// 	int	x;
// 	int	y;
// 	int	dist_sq;
// 	int	r_sq;
// 	int	inner_sq;

// 	r_sq = circle.radius * circle.radius;
// 	inner_sq = (circle.radius - MM_BORDER_THICKNESS)
// 		* (circle.radius - MM_BORDER_THICKNESS);
// 	y = -circle.radius;
// 	while (y <= circle.radius)
// 	{
// 		x = -circle.radius;
// 		while (x <= circle.radius)
// 		{
// 			dist_sq = x * x + y * y;
// 			if (dist_sq <= r_sq)
// 			{
// 				if (dist_sq >= inner_sq)
// 					put_pixel(img, circle.cx + x, circle.cy + y, border_color);
// 				else
// 					put_pixel(img, circle.cx + x, circle.cy + y, MM_BG_COLOR);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// /*
// ** Draws player field of view lines
// ** @param m: Main game structure
// ** @param circle: Minimap circle
// */
// static void	draw_fov(t_maze *m, t_circle circle)
// {
// 	t_player	*p;
// 	double		lx;
// 	double		ly;
// 	double		rx;
// 	double		ry;
// 	int			i;

// 	p = &m->map.player;
// 	lx = p->dir.x;
// 	ly = p->dir.y;
// 	rx = p->dir.x;
// 	ry = p->dir.y;
// 	rotate_vector(&lx, &ly, FOV_ANGLE / 2);
// 	rotate_vector(&rx, &ry, -FOV_ANGLE / 2);
// 	i = 0;
// 	while (i < MM_RADIUS)
// 	{
// 		if (is_inside_circle(circle.cx, circle.cy,
// 				circle.cx + lx * i, circle.cy + ly * i, MM_RADIUS))
// 			put_pixel(&m->img, circle.cx + lx * i, circle.cy + ly * i, 0xAD0900);
// 		if (is_inside_circle(circle.cx, circle.cy,
// 				circle.cx + rx * i, circle.cy + ry * i, MM_RADIUS))
// 			put_pixel(&m->img, circle.cx + rx * i, circle.cy + ry * i, 0xAD0900);
// 		i++;
// 	}
// }

// /*
// ** Gets minimap circle parameters
// ** @return: Circle structure with minimap parameters
// */
// static t_circle	get_minimap_circle(void)
// {
// 	t_circle	circle;

// 	circle.cx = MM_PADDING + MM_RADIUS;
// 	circle.cy = MM_PADDING + MM_RADIUS;
// 	circle.radius = MM_RADIUS;
// 	return (circle);
// }

// /*
// ** Draws complete minimap
// ** @param m: Main game structure
// */
// void	draw_minimap(t_maze *m)
// {
// 	t_circle	circle;
// 	t_rect		rect;
// 	int			x;
// 	int			y;

// 	circle = get_minimap_circle();
// 	draw_circle_border(&m->img, (t_circle){circle.cx, circle.cy,
// 		MM_RADIUS + 10}, 0x63120D);
// 	y = 0;
// 	while (y < m->map.height)
// 	{
// 		x = 0;
// 		while (x < m->map.width)
// 		{
// 			rect.x = circle.cx + (x - m->map.player.pos.x) * MM_TILE;
// 			rect.y = circle.cy + (y - m->map.player.pos.y) * MM_TILE;
// 			rect.width = MM_TILE;
// 			rect.height = MM_TILE;
// 			if (is_inside_circle(circle.cx, circle.cy, rect.x, rect.y, MM_RADIUS))
// 			{
// 				if (m->map.grid[y][x] == '1')
// 					draw_square_clipped(&m->img, rect, circle, 0x222222);
// 				else
// 					draw_square_clipped(&m->img, rect, circle, 0x888888);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	draw_circle(&m->img, circle, 0xAD0900);
// 	draw_fov(m, circle);
// }




































// #include "cub3d.h"

// void put_pixel(t_img *img, int x, int y, int color)
// {
//     t_maze *maze = *maze_struct();

//     if (x < 0 || x >= img->width || y < 0 || y >= img->height) // is the last condition necessery
//         return;

//     char *px = img->addr + (y * img->line_len + x * (img->bpp / 8));
//     *(unsigned int *)px = color;
// }
// static int inside_circle(int cx, int cy, int x, int y, int r)
// {
//     int dx = x - cx;
//     int dy = y - cy;
//     return (dx * dx + dy * dy <= r * r);
// }
// void draw_square_clipped(
//     t_img *img,
//     int sx,
//     int sy,
//     int size,
//     int color,
//     int cx,
//     int cy,
//     int radius)
// {
//     int x;
//     int y;

//     y = 0;
//     while (y < size)
//     {
//         x = 0;
//         while (x < size)
//         {
//             if (inside_circle(cx, cy, sx + x, sy + y, radius))
//                 put_pixel(img, sx + x, sy + y, color);
//             x++;
//         }
//         y++;
//     }
// }



// void draw_circle(t_img *img, int cx, int cy, int r, int color)
// {
//     int x;
//     int y;

//     y = -r;
//     while (y <= r)
//     {
//         x = -r;
//         while (x <= r)
//         {
//             if (x * x + y * y <= r * r)
//                 put_pixel(img, cx + x, cy + y, color);
//             x++;
//         }
//         y++;
//     }
// }


// void draw_square(t_img *img, int sx, int sy, int size, int color)
// {
//     int y = 0;
//     int x;

//     while (y < size)
//     {
//         x = 0;
//         while (x < size)
//         {
//             put_pixel(img, sx + x, sy + y, color);
//             x++;
//         }
//         y++;
//     }
// }
// static void rotate(double *x, double *y, double angle)
// {
//     double old_x = *x;
//     *x = old_x * cos(angle) - *y * sin(angle);
//     *y = old_x * sin(angle) + *y * cos(angle);
// }

// void draw_circle_border(
//     t_img *img,
//     int cx,
//     int cy,
//     int radius,
//     int border_color
// )
// {
//     int y;
//     int x;

//     for (y = -radius; y <= radius; y++)
//     {
//         for (x = -radius; x <= radius; x++)
//         {
//             int dist_sq = x * x + y * y;
//             int r_sq = radius * radius;
//             int inner_sq = (radius - MM_BORDER_THICKNESS)
//                             * (radius - MM_BORDER_THICKNESS);

//             // outside circle → ignore
//             if (dist_sq > r_sq)
//                 continue;

//             // border
//             if (dist_sq >= inner_sq)
//             {
//                 put_pixel(img, cx + x, cy + y, border_color);
//             }
//             // background
//             else
//             {
//                 put_pixel(img, cx + x, cy + y, MM_BG_COLOR);
//             }
//         }
//     }
// }

// void draw_fov(t_maze *m, int cx, int cy)
// {
//     t_player *p = &m->map.player;

//     double lx = p->dir.x;
//     double ly = p->dir.y;
//     double rx = p->dir.x;
//     double ry = p->dir.y;

//     rotate(&lx, &ly,  FOV_ANGLE / 2);
//     rotate(&rx, &ry, -FOV_ANGLE / 2);

//     int i = 0;
//     while (i < MM_RADIUS)
//     {
//         if (inside_circle(cx, cy,
//             cx + lx * i,
//             cy + ly * i,
//             MM_RADIUS))
//             put_pixel(&m->img,
//                 cx + lx * i,
//                 cy + ly * i,
//                 0xAD0900);

//         if (inside_circle(cx, cy,
//             cx + rx * i,
//             cy + ry * i,
//             MM_RADIUS))
//             put_pixel(&m->img,
//                 cx + rx * i,
//                 cy + ry * i,
//                 0xAD0900);
//         i++;
//     }
// }

// void render_minimap(t_maze *m)
// {
//     draw_circle_border(&m->img, MM_PADDING + MM_RADIUS, MM_PADDING + MM_RADIUS, MM_RADIUS + 10, 0x63120D);
//     int cx = MM_PADDING + MM_RADIUS;
//     int cy = MM_PADDING + MM_RADIUS;

//     int x;
//     int y;

//     y = 0;
//     while (y < m->map.height)
//     {
//         x = 0;
//         while (x < m->map.width)
//         {
//             int draw_x = cx + (x - m->map.player.pos.x) * MM_TILE;
//             int draw_y = cy + (y - m->map.player.pos.y) * MM_TILE;

//             if (inside_circle(cx, cy, draw_x, draw_y, MM_RADIUS))
//             {
//                 if (m->map.grid[y][x] == '1')
//                     draw_square_clipped(&m->img, draw_x, draw_y, MM_TILE, 0x222222, cx, cy, MM_RADIUS);
//                 else
//                     draw_square_clipped(&m->img, draw_x, draw_y, MM_TILE, 0x888888, cx, cy, MM_RADIUS);
//             }
//             x++;
//         }
//         y++;
//     }
//     draw_circle(&m->img, cx, cy, 4, 0xAD0900); draw_fov(m, cx, cy);
// }