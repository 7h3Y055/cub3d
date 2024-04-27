#include "cub3d.h"

// void    create_square(t_img_data *img, size_t ray_l)
// {
//     size_t y = (WIDTH / 2) - (ray_l / 2);
//     size_t x = 0;

//     while (y < (WIDTH / 2) + (144 / 2))
//     {
//         x = 0;
//         while (x < HEIGHT / 4)
//         {
//             my_mlx_pixel_put(img, x, y, 0xffffffff);
//             x ++;
//         }
//         y++;
//     }
    
// }

void    create_square(t_img_data *img, size_t ray_l, size_t ray_c, size_t n)
{
    size_t y = (WIDTH / 2) - (ray_l / 2);
    size_t x = 8 * n;

    // while (y < (WIDTH / 2) + (ray_l / 2))
    // {
    //     x = WIDTH / ray_c * n;
    //     while (x < HEIGHT / ray_c)
    //     {
            my_mlx_pixel_put(img, x, y, 0xffffffff);
    //         x ++;
    //     }
    //     y++;
    // }
    
}

void test(t_ptr *ptr)
{
    t_img_data img;
    size_t      x;
    size_t      y;

    void *win = mlx_new_window(ptr->win.mlx, HEIGHT, WIDTH, "Cub3D raycast");
	img.img = mlx_new_image(ptr->win.mlx,HEIGHT ,WIDTH);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
				&img.endian);
    y = WIDTH / 2;
    x = 0;
    while (x < HEIGHT)
    {
        my_mlx_pixel_put(&img, x, y, 0xffffffff);
        x++;
    }
    create_square(&img, 100, 4, 0);
    create_square(&img, 200, 4, 1);
    create_square(&img, 300, 4, 2);
    create_square(&img, 400, 4, 3);
    mlx_put_image_to_window(ptr->win.mlx, win, img.img, 0, 0);
}