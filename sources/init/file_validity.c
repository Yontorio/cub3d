#include <cub3d.h>

static bool path_validity(char *file_path)
{
	char	*last_slash;
	int		len;

	len = ft_strlen(file_path);
	if (len <= 4)
		return (false);
	last_slash = ft_strrchr(file_path, '/');
	if (last_slash && ft_strlen(last_slash) <= 5)
		return (false);
	else if (ft_strncmp(file_path + (len - 4), ".cub", 4))
		return (false);
	return (true);
}
bool file_validity(int argc, char **argv)
{
    if (!(argc == 2 && path_validity(argv[1])))
    {
        write(2, "Usage: ./Cub3d map.cub", 22);
		return (false);
    }
	return (true);
}
