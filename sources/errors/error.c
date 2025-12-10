#include <cub3d.h>

bool    error_exit(char *error_msg)
{
	write(STDERR_FILENO, "ETERNAL MAZE", ft_strlen("ETERNAL MAZE"));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
	fd_storage(CLOSE);
	destroy_maze();
	destroy_everything();
	exit(EXIT_FAILURE);
}
