#include "cub3d.h"

// void	my_mlx_pixe(t_img_data *img, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// my_mlx_pixel_put(&ptr->win.img, (size_t)(next.x / SCALE * DEBUG_SCALE) / DEBUG_SCALE * DEBUG_SCALE, next.y / SCALE * DEBUG_SCALE, yellow);



// int scaleBetween(size_t unscaledNum, size_t minAllowed, size_t maxAllowed, size_t min, size_t max) {
//   return (maxAllowed - minAllowed) * (unscaledNum - min) / (max - min) + minAllowed;
// }
//scaleBetween(y, 0, ptr->texture.no_h, min, max)
int get_pixel_color(t_ptr *ptr, t_point next, size_t y, size_t first_point_in_wall, double ray_l)
{

    char *dst;
    int img_y;
    int img_x;

    if (next.face == GREEN || next.face == GRAY)
    {
        img_x = (next.y - (long long)next.y / SCALE * SCALE) * ptr->texture.no_w / SCALE;
    }
    else
    {
        img_x = (next.x - (long long)next.x / SCALE * SCALE) * ptr->texture.no_w / SCALE;
    }
    
    img_y = (y - first_point_in_wall) * ((double)ptr->texture.no_h / ray_l);
    
    // printf ("%d\n", img_);
    if (img_y < 0 || img_y > ptr->texture.no_h)
        return (-1);
    if (img_x < 0 || img_x > ptr->texture.no_w)    
        return (-1);
    
    // else
    // {
    //     return (GREEN);
    //     // img_x = (int)next.x % ptr->texture.no_h;
    //     // img_y = next.y - (long long)next.y / SCALE * SCALE;
    //     // img_y = img_y * ptr->texture.no_w / SCALE;
    // }


	dst = ptr->texture.no_img.addr + (img_y * ptr->texture.no_img.line_length + img_x * (ptr->texture.no_img.bits_per_pixel / 8));
    // return (GREEN);
    return (*(int*)dst);
}



void    create_square(t_ptr *ptr, double ray_l, size_t x, t_point next)
{
    double  y;
    double  dy;
    int color;
    ray_l =  (SCALE * HEIGHT) / ray_l;
    dy =  (WIDTH / 2) - (ray_l / 2);
    y = 0;

    while (y < dy)
    {
        my_mlx_pixel_put(&ptr->img3d, x, y, rgb2int(ptr->parse.ceiling[0], ptr->parse.floor[1], ptr->parse.floor[2]));
        y++;
    }

    while (y < (WIDTH / 2) + (ray_l / 2))
    {
        color = get_pixel_color(ptr, next, (size_t)y, dy, ray_l);
        if (!(color == -1 || x < 0 || x > HEIGHT || y < 0 || y > WIDTH))
            my_mlx_pixel_put(&ptr->img3d, x, y, color);
        y++;
    }

    while (y < WIDTH)
    {
        my_mlx_pixel_put(&ptr->img3d, x, y, rgb2int(ptr->parse.floor[0], ptr->parse.ceiling[1], ptr->parse.ceiling[2]));
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
