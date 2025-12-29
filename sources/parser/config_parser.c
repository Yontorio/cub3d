#include "cub3d.h"

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
	else if (is_map_line(lines[i][0]))
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
    if (!(cnt.textures == 4 && cnt.colors == 2 && cnt.map == 1))
        error_exit("Missing or invalid line in .cub file");
}

bool config_parser(int ac, char **av)
{
    char	**lines;
    char    *file;

    if (!file_validity(ac, av))
        return (false);
    set_current_section(TEMPORARY);
    file = read_file(av[1]);
    lines = split_lines(file);
    set_current_section(REMAINS);
    process_lines(lines);
    return (true);
}
