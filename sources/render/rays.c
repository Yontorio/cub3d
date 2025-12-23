#include "cub3d.h"

static inline t_vec v_add(t_vec a, t_vec b)
{
    return (t_vec){a.x + b.x, a.y + b.y};
}

static inline t_vec v_scale(t_vec v, double s)
{
    return (t_vec){v.x * s, v.y * s};
}

int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}

void	init_ray(t_maze *m, int x, t_vec *ray)
{
	double	cam_x;

	cam_x = 2.0 * x / (double)m->win_w - 1.0;
	*ray = v_add(m->map.player.dir, v_scale(m->map.player.plane, cam_x));
}

void	init_dda(t_player *p, t_vec *ray, t_dda *d)
{
	d->map_x = (int)p->pos.x;
	d->map_y = (int)p->pos.y;
	d->delta_x = (ray->x == 0) ? 1e30 : fabs(1 / ray->x);
	d->delta_y = (ray->y == 0) ? 1e30 : fabs(1 / ray->y);
	d->step_x = (ray->x < 0) ? -1 : 1;
	d->side_x = (ray->x < 0) ? (p->pos.x - d->map_x) * d->delta_x
		: (d->map_x + 1.0 - p->pos.x) * d->delta_x;
	d->step_y = (ray->y < 0) ? -1 : 1;
	d->side_y = (ray->y < 0) ? (p->pos.y - d->map_y) * d->delta_y
		: (d->map_y + 1.0 - p->pos.y) * d->delta_y;
	d->tile = '\0';
}

void	perform_dda(t_maze *m, t_dda *d)
{
	while (1)
	{
		if (d->side_x < d->side_y)
		{
			d->side_x += d->delta_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_y += d->delta_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (m->map.grid[d->map_y][d->map_x] == '1'
		|| m->map.grid[d->map_y][d->map_x] == 'D')
		{
			d->tile = m->map.grid[d->map_y][d->map_x];
			break ;
		}
	}
}

double	calc_distance(t_player *p, t_dda *d, t_vec *ray)
{
	double	dist;

	if (d->side == 0)
		dist = (d->map_x - p->pos.x + (1 - d->step_x) / 2) / ray->x;
	else
		dist = (d->map_y - p->pos.y + (1 - d->step_y) / 2) / ray->y;
	return (dist);
}

void	calc_line_height(t_maze *m, double dist, t_line *line)
{
	line->height = (int)(m->win_h / dist);
	line->start = -line->height / 2 + m->win_h / 2;
	line->end = line->height / 2 + m->win_h / 2;
	if (line->start < 0)
		line->start = 0;
	if (line->end >= m->win_h)
		line->end = m->win_h - 1;
}

int	get_tex_id(t_vec *ray, t_dda dda)
{
	if (dda.tile == 'D')
	{
		return (DOOR);
	}
	else if (dda.tile =='1')
	{
		if (dda.side == 0 && ray->x > 0)
			return (EAST);
		else if (dda.side == 0 && ray->x < 0)
			return (WEST);
		else if (dda.side == 1 && ray->y > 0)
			return (SOUTH);
		else
			return (NORTH);		
	}
	return (0);

}

double	get_wall_x(t_player *p, t_vec *ray, int side, double dist)
{
	double	wall_x;

	if (side == 0)
		wall_x = p->pos.y + dist * ray->y;
	else
		wall_x = p->pos.x + dist * ray->x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	draw_textured_line(t_maze *m, int x, t_line *line, t_tex_info *tex)
{
	double	tex_pos;
	double	step;
	int		y;
	int		color;

	step = 1.0 * tex->img->height / line->height;
	tex_pos = (line->start - m->win_h / 2 + line->height / 2) * step;
	y = line->start;
	while (y <= line->end)
	{
		tex->y = (int)tex_pos & (tex->img->height - 1);
		tex_pos += step;
		color = get_tex_pixel(tex->img, tex->x, tex->y);
		put_pixel(&m->img, x, y, color);
		y++;
	}
}

void	raycasting(t_maze *m)
{
	int		x;
	t_vec	ray;
	t_dda	dda;
	t_line	line;
	t_tex_info	tex;

	x = 0;
	while (x < m->win_w)
	{
		init_ray(m, x, &ray);
		init_dda(&m->map.player, &ray, &dda);
		perform_dda(m, &dda);
		line.dist = calc_distance(&m->map.player, &dda, &ray);
		calc_line_height(m, line.dist, &line);
		tex.id = get_tex_id(&ray, dda);
		tex.img = &m->tex[tex.id];
		tex.wall_x = get_wall_x(&m->map.player, &ray, dda.side, line.dist);
		tex.x = (int)(tex.wall_x * tex.img->width);
		if ((dda.side == 0 && ray.x > 0) || (dda.side == 1 && ray.y < 0))
			tex.x = tex.img->width - tex.x - 1;
		draw_textured_line(m, x, &line, &tex);
		x++;
	}
}
