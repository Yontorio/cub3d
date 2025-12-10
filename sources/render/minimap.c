#include "cub3d.h"

void put_pixel(t_img *img, int x, int y, int color)
{
    t_maze *maze = *maze_struct();

    if (x < 0 || x >= img->width || y < 0 || y >= img->height) // is the last condition necessery
        return;

    char *px = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)px = color;
}

// void render_background(t_maze *maze, int color)
// {
//     int y = 0;
//     int x;
//     int pixel;

//     while (y < maze->win_h)
//     {
//         x = 0;
//         while (x < maze->win_w)
//         {
//             pixel = y * maze->img.line_len + x * (maze->img.bpp / 8);
//             *(unsigned int *)(maze->img.addr + pixel) = color;
//             x++;
//         }
//         y++;
//     }
// }


void draw_square(t_img *img, int sx, int sy, int size, int color)
{
    int y = 0;
    int x;

    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            put_pixel(img, sx + x, sy + y, color);
            x++;
        }
        y++;
    }
}


void draw_minimap(t_maze *maze)
{
    int t = 8;
    int y = 0;
    int x;

    while (y < maze->map.height)
    {
        x = 0;
        while (x < maze->map.width)
        {
            if (maze->map.grid[y][x] == '1')
                draw_square(&maze->img, x * t, y * t, t, 0x333333);
            else
                draw_square(&maze->img, x * t, y * t, t, 0x777777);
            x++;
        }
        y++;
    }

    int px = maze->map.player.pos.x * t;
    int py = maze->map.player.pos.y * t;

    put_pixel(&maze->img, px, py, 0xFF0000);
}



// void draw_direction(t_maze *maze)
// {
//     int tile = 12;

//     int px = maze->map.player.pos_x * tile;
//     int py = maze->map.player.pos_y * tile;

//     int dx = px + maze->map.player.dir_x * (tile * 2);
//     int dy = py + maze->map.player.dir_y * (tile * 2);

//     for (int i = 0; i < tile * 2; i++)
//     {
//         int xx = px + (maze->map.player.dir_x * i);
//         int yy = py + (maze->map.player.dir_y * i);
//         put_pixel(&maze->img, xx, yy, 0xFFAA00);  // orange
//     }
// }

// void draw_minimap(t_maze *maze)
// {
//     int tile = 32;

//     for (int y = 0; y < maze->map.height; y++)
//     {
//         for (int x = 0; x < maze->map.width; x++)
//         {
//             if (maze->map.grid[y][x] == '1')
//                 draw_square(&maze->img, x * tile, y * tile, tile, 0x333333);
//             else
//                 draw_square(&maze->img, x * tile, y * tile, tile, 0x777777);
//         }
//     }

//     int px = maze->map.player.pos_x * tile;
//     int py = maze->map.player.pos_y * tile;

//     // put_pixel(&maze->img, px, py, 0xFF0000);
//     draw_square(&maze->img, px - tile/4, py - tile/4, tile/2, 0xFF0000);
//     draw_direction(maze);
// }

// void render_background(t_maze *maze, int color)
// {
//     int x, y;

//     for (y = 0; y < maze->win_h; y++)
//     {
//         for (x = 0; x < maze->win_w; x++)
//         {
//             int pixel = y * maze->img.line_len + x * (maze->img.bpp / 8);
//             *(unsigned int *)(maze->img.addr + pixel) = color;
//         }
//     }
//     mlx_put_image_to_window(maze->mlx, maze->win, maze->img.img, 0, 0);
// }

// int render(t_maze *maze)
// {
//     render_background(maze, 0x202020);

//     draw_minimap(maze);

//     mlx_put_image_to_window(maze->mlx, maze->win, maze->img.img, 0, 0);

//     return 0;
// }
