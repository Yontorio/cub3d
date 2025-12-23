#include <cub3d.h>

t_maze **maze_struct()
{
    static t_maze *maze = NULL;

    if (maze == NULL)
    {
        init_maze(&maze);
    }
    return (&maze);
}
