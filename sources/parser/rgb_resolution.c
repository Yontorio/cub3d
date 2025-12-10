#include "cub3d.h"

static int is_valid_rgb(int n)
{
    return (n >= 0 && n <= 255);
}

static int assemble_rgb(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static void set_color(char type, int r, int g, int b)
{
    t_env   *env;

    env = &((*maze_struct())->env);
    if (!is_valid_rgb(r) || !is_valid_rgb(g) || !is_valid_rgb(b))
        error_exit("Invalid RGB color: must be 0-255");

    if (type == 'F')
        env->floor = assemble_rgb(r, g, b);
    else if (type == 'C')
        env->ceiling = assemble_rgb(r, g, b);
}

void parse_color_line(char *line)
{
    char    **parts;
    char    **rgb;
    int      r, g, b;

    parts = ft_split(line, " ");
    if (!parts || !parts[0] || !parts[1])
        error_exit("Invalid color line");

    rgb = ft_split(parts[1], ",");
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
        error_exit("Invalid RGB format");

    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);

    set_color(parts[0][0], r, g, b);
}
