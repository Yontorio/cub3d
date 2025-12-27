#include "cub3d.h" // need some review about fd and alloc leaks

static int	safe_read(int fd, char *buffer, int size)
{
	int	i;

	i = read(fd, buffer, size);
	if (i < 0)
	{
		error_exit("Read failure");
	}
	return (i);
}

static char *read_loop(int fd, char *been_read)
{
	char	buffer[51];
    int     i;

    while (true)
    {
        i = safe_read(fd, buffer, 50);
        if (!i)
			break;
        buffer[i] = '\0';
        been_read = join_two_strings(been_read , buffer, "");
    }
	fd_storage(CLOSE);
    return (been_read);
}


char	*read_file(char *file_path)
{
	char	buffer[51];
	char	*retval;
	int 	fd;
	int		i;

    fd = safe_open(file_path, O_RDONLY);
	i = safe_read(fd, buffer, 50); 
	if (!i)
    {
        error_exit("Config file is empty");
    }
	buffer[i] = '\0';
	return (read_loop(fd, ft_strdup(buffer)));
}
