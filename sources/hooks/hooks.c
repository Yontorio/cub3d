#include "cub3d.h"

static int is_wall(t_maze *m, double y, double x)
{
    return (m->map.grid[(int)y][(int)x] == '1'
             || m->map.grid[(int)y][(int)x] == 'D');
}

void move_forward(t_maze *m, t_player *p)
{
    double next_x = p->pos.x + p->dir.x * MOVE_SPEED;
    double next_y = p->pos.y + p->dir.y * MOVE_SPEED;

    if (!is_wall(m, p->pos.y, next_x))
        p->pos.x = next_x;
    if (!is_wall(m, next_y, p->pos.x))
        p->pos.y = next_y;
}


void move_backward(t_maze *m, t_player *p)
{
    double next_x = p->pos.x - p->dir.x * MOVE_SPEED;
    double next_y = p->pos.y - p->dir.y * MOVE_SPEED;

    if (!is_wall(m, p->pos.y, next_x))
        p->pos.x = next_x;
    if (!is_wall(m, next_y, p->pos.x))
        p->pos.y = next_y;
}

void move_left(t_maze *m, t_player *p)
{
    double px = p->dir.y;
    double py = -p->dir.x;

    double next_x = p->pos.x + px * MOVE_SPEED;
    double next_y = p->pos.y + py * MOVE_SPEED;

    if (!is_wall(m, p->pos.y, next_x))
        p->pos.x = next_x;
    if (!is_wall(m, next_y, p->pos.x))
        p->pos.y = next_y;
}


void move_right(t_maze *m, t_player *p)
{
    double px = -p->dir.y;
    double py = p->dir.x;

    double next_x = p->pos.x + px * MOVE_SPEED;
    double next_y = p->pos.y + py * MOVE_SPEED;

    if (!is_wall(m, p->pos.y, next_x))
        p->pos.x = next_x;
    if (!is_wall(m, next_y, p->pos.x))
        p->pos.y = next_y;
}

void rotate(t_player *p, double angle)
{
    double old_dir_x = p->dir.x;
    double old_plane_x = p->plane.x;

    p->dir.x = p->dir.x * cos(angle) - p->dir.y * sin(angle);
    p->dir.y = old_dir_x * sin(angle) + p->dir.y * cos(angle);

    p->plane.x = p->plane.x * cos(angle) - p->plane.y * sin(angle);
    p->plane.y = old_plane_x * sin(angle) + p->plane.y * cos(angle);
}

static void	try_open_door(t_maze *m)
{
	t_player	*p;
	int			tx;
	int			ty;

	p = &m->map.player;
	tx = (int)(p->pos.x + p->dir.x);
	ty = (int)(p->pos.y + p->dir.y);

	if (m->map.grid[ty][tx] == 'D')
		m->map.grid[ty][tx] = 'd';
	else if (m->map.grid[ty][tx] == 'd')
		m->map.grid[ty][tx] = 'D';
}

int key_press(int key, t_maze *maze)
{
    if (key == KEY_ESC)
        close_window();
    else if (key == KEY_W)
        maze->keys.w = 1;
    else if (key == KEY_S)
        maze->keys.s = 1;
    else if (key == KEY_A)
        maze->keys.a = 1;
    else if (key == KEY_D)
        maze->keys.d = 1;
    else if (key == KEY_LEFT)
        maze->keys.left = 1;
    else if (key == KEY_RIGHT)
        maze->keys.right = 1;
    return (0);
}

int key_release(int key, t_maze *maze)
{
    if (key == KEY_E)
	    try_open_door(maze);
    else if (key == KEY_W)
        maze->keys.w = 0;
    else if (key == KEY_S)
        maze->keys.s = 0;
    else if (key == KEY_A)
        maze->keys.a = 0;
    else if (key == KEY_D)
        maze->keys.d = 0;
    else if (key == KEY_LEFT)
        maze->keys.left = 0;
    else if (key == KEY_RIGHT)
        maze->keys.right = 0;
    return (0);
}

int render_maze(t_maze *maze)
{
    t_player *p = &maze->map.player;

    if (maze->keys.w)
        move_forward(maze, p);
    if (maze->keys.s)
        move_backward(maze, p);
    if (maze->keys.a)
        move_left(maze, p);
    if (maze->keys.d)
        move_right(maze, p);
    if (maze->keys.right)
        rotate(p, ROT_SPEED);
    if (maze->keys.left)
        rotate(p, -ROT_SPEED);
    render_frame(maze);
    return (0);
}

int mouse_rotate(int x, int y, t_maze *maze)
{
    int dx;

    dx = x - maze->mouse_x;
    maze->mouse_x = x;
    rotate(&maze->map.player, dx * MOUSE_SENSOR);
    return (0);
}

int close_window(void)
{
    destroy_maze();
    destroy_everything();
    exit(EXIT_SUCCESS);
    return (0);
}
