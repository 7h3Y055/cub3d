#include "cub3d.h"

void    create_square(t_img_data *img, size_t ray_l, size_t ray_c, size_t n)
{
    size_t y = (WIDTH / 2) - (ray_l / 2);
    size_t x;

    while (y < (WIDTH / 2) + (ray_l / 2))
    {
        x = HEIGHT / ray_c * n;
        while (x < (HEIGHT / ray_c) * (n + 1))
        {
            my_mlx_pixel_put(img, x, y, 0xFFFFFF);
            x ++;
        }
        y++;
    }
}

void midle_line(t_ptr *ptr)
{
    t_img_data img = ptr->img3d;
    size_t      x;
    size_t      y;

    y = WIDTH / 2;
    x = 0;
    while (x < HEIGHT)
    {
        my_mlx_pixel_put(&img, x, y, 0xFF0000);
        x++;
    }
}
