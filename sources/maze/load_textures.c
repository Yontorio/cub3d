#include <cub3d.h>

void    load_textures(t_maze *maze)
{
    char    *tex_paths[4];
    int     i;

    i = -1;
    tex_paths[0] = maze->env.no;
    tex_paths[1] = maze->env.so;
    tex_paths[2] = maze->env.we;
    tex_paths[3] = maze->env.ea;
    while (++i < 4)
    {
        maze->tex[i].img = mlx_xpm_file_to_image(maze->mlx,
                                            tex_paths[i],
                                            &maze->tex[i].width,
                                            &maze->tex[i].height);
        if (!maze->tex[i].img)
            error_exit("Error\nFailed to load XPM texture");
        maze->tex[i].addr = mlx_get_data_addr(maze->tex[i].img,
                                        &maze->tex[i].bpp,
                                        &maze->tex[i].line_len,
                                        &maze->tex[i].endian);
    }
}


// void    free_textures(t_maze *m) // it must be added to destory everything
// {
//     for (int i = 0; i < 4; i++)
//     {
//         if (m->tex[i].img)
//             mlx_destroy_image(m->mlx, m->tex[i].img);
//     }
// }