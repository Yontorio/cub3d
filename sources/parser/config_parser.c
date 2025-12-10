#include "cub3d.h"

// static void process_lines(char **lines)
// {
//     t_maze *maze = *maze_struct();
//     int textures = 0;
//     int colors = 0;
//     int map = 0;
//     char *line;
//     int i = -1;

//     while (lines[++i])
//     {
//         line = lines[i];
//         if (!line || line[0] == '\0')
//             continue;
//         if (!ft_strncmp(line, "NO", 2) ||
//             !ft_strncmp(line, "SO", 2) ||
//             !ft_strncmp(line, "WE", 2) ||
//             !ft_strncmp(line, "EA", 2))
//         {
//             parse_texture_line(&maze->env, line);
//             textures++;
//             continue;
//         }
//         if (line[0] == 'F' || line[0] == 'C')
//         {
//             parse_color_line(&maze->env, line);
//             colors++;
//             continue;
//         }
//         if (is_map_line(line))
//         {
//             extract_map(&maze->map, &lines[i]);
//             map++;
//             break;
//         }
//         error_exit("Invalid line in .cub file"); // is a space in empty line a problem?
//     }
//     if (!(textures == 4 && colors == 2 && map == 1)) // is it necessery? maybe textures & colors should
//         error_exit("Invalid line in .cub file"); // overide it only check if the minimal is there!?
// }


static bool	is_texture_line(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) ||
        !ft_strncmp(line, "SO ", 3) ||
		!ft_strncmp(line, "WE ", 3) ||
        !ft_strncmp(line, "EA ", 3))
		return (true);
	return (false);
}

static bool	is_color_line(char *line)
{
	if (line[0] == 'F' || line[0] == 'C')
		return (true);
	return (false);
}

static void	process_line_content(char **lines, int i, t_cnt *cnt)
{
	if (is_texture_line(lines[i]))
	{
		parse_texture_line(lines[i]);
		cnt->textures++;
	}
	else if (is_color_line(lines[i]))
	{
		parse_color_line(lines[i]);
		cnt->colors++;
	}
	else if (is_map_line(lines[i]))
	{
		extract_map(&lines[i]);
		cnt->map++;
	}
	else
		error_exit("Invalid line in .cub file"); // is a space in empty line a problem?
}
static void process_lines(char **lines)
{
    t_cnt   cnt; 
    int     i;

    i = -1;
    ft_memset(&cnt, 0, sizeof(t_cnt));
    while (lines[++i])
    {
        if (lines[i][0] == '\0')
            continue;
        process_line_content(lines, i, &cnt);
		if (cnt.map == 1)
			break ;
    }
    if (!(cnt.textures == 4 && cnt.colors == 2 && cnt.map == 1)) // is it necessery? maybe textures & colors should
        error_exit("Missing or invalid line in .cub file"); // overide it only check if the minimal is there!?
}



bool config_parser(int ac, char **av)
{
    char	**lines;
    char    *file;

    if (!file_validity(ac, av))
        return (false);
    set_current_section(TEMPORARY);
    file = read_file(av[1]);
    lines = ft_split(file, "\n");
    set_current_section(REMAINS);
    process_lines(lines);
    return (true);
}
