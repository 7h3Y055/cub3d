#include "cub3d.h"

void    create_square(t_img_data *img, size_t ray_l, size_t x, int color)
{
    size_t  y;
    ray_l =  ((SCALE - 20) * HEIGHT) / ray_l;
    if (ray_l > WIDTH)
        ray_l = WIDTH;
    y =  (WIDTH / 2) - (ray_l / 2);
    while (y < (WIDTH / 2) + (ray_l / 2) - 1)
    {
        my_mlx_pixel_put(img, x, y, color);
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
