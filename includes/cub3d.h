#ifndef CUB3D_H
# define CUB3D_H

// Eternal Maze 

# include "librairies.h"
# include "memtrack.h"
# include "stdfcts.h"
# include "utils.h"

# include "mlx.h"

# define INITIAL_CAPACITY 64

# define MOVE_SPEED 0.2
# define ROT_SPEED 0.1

# define KEY_ESC   53
# define KEY_W     13
# define KEY_S     1
# define KEY_A     0
# define KEY_D     2
# define KEY_LEFT  124
# define KEY_RIGHT 123


typedef struct s_dda
{
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_dda;

typedef struct s_line
{
	int		height;
	int		start;
	int		end;
	double	dist;
}	t_line;

typedef struct s_cnt
{
    int textures;
    int colors;
    int map;
} t_cnt;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     height;
    int     width;
}   t_img;

typedef struct s_tex_info
{
	t_img	*img;
	int		id;
	double	wall_x;
	int		x;
	int		y;
}	t_tex_info;

typedef struct s_vec
{
    double x;
    double y;
}   t_vec;

typedef enum e_tex_id
{
    NORTH = 0,
    SOUTH,
    WEST,
    EAST
}   t_tex_id;

typedef struct s_player
{
    t_vec  pos;
    t_vec  dir;
    t_vec  plane;
}   t_player;

typedef struct s_env {
    char *no;
    char *so;
    char *we;
    char *ea;

    int floor;
    int ceiling;
} t_env;

typedef struct s_map
{
    char        **grid;
    int         width;
    int         height;
    t_player    player;
}   t_map;

typedef struct s_maze
{
    void        *mlx;
    void        *win;

    int         win_w;
    int         win_h;

    t_img       img;

    t_env       env;
    t_map       map;

    t_img       tex[4];
}   t_maze;



void	destroy_maze(void);
bool     config_parser(int ac, char **av);
bool    init_maze(t_maze **maze);
void    init_env(t_env *env);
void    init_img(t_img *img);
void    init_map(t_map *map);
bool    file_validity(int argc, char **argv);
void    extract_map(char **lines);
int     eternal_maze(void);
bool    maze_setup(void);
bool    error_exit(char *error_msg);
t_maze **maze_struct(void);
int render_all(t_maze *maze);
void draw_minimap(t_maze *maze);
void render_maze(t_maze *m);
void put_pixel(t_img *img, int x, int y, int color);

void load_textures(t_maze *m);


int     key_handler(int key, t_maze *maze);
int     close_window(void);

// void    render_background(t_maze *maze, int color);


void parse_texture_line(char *line);
void parse_color_line(char *line);
int is_map_line(char *line);
void parse_player(t_map *map);
void normalize_map(t_map *map);
void check_map_chars(t_map *map);
void check_map_closed(t_map *map);



#endif
