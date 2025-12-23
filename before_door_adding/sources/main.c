#include <cub3d.h>

int main(int ac, char **av)
{
    if (config_parser(ac, av))
    {
        if (maze_setup())
        {
            return (eternal_maze());
        }
    }
    return (EXIT_FAILURE);
}
