#include "cub3d.h"

int init_img_yx(t_ptr *ptr, t_point next, int *img_y, int *img_x, int y)
{

    int w;
    int h;


    if (next.face == WHITE)
    {
        w = ptr->texture.no_w;
        h = ptr->texture.no_h;
    }
    if (next.face == BLEU)
        {
        w = ptr->texture.so_w;
        h = ptr->texture.so_h;
    }
    if (next.face == GREEN)
        {
        w = ptr->texture.we_w;
        h = ptr->texture.we_h;
    }
    if (next.face == GRAY)
        {
        w = ptr->texture.ea_w;
        h = ptr->texture.ea_h;
    }

    if (next.face == GREEN || next.face == GRAY)
        *img_x = (next.y - (long long)next.y / SCALE * SCALE) * w / SCALE;
    else
        *img_x = (next.x - (long long)next.x / SCALE * SCALE) * w / SCALE;

    *img_y = (y - next.first_point_in_wall) * (h / next.ray_l);
    
    if (*img_y < 0 || *img_y >= h || *img_x < 0 || *img_x >= w)
        return (-1);
    return (0);
}


int get_pixel_color(t_ptr *ptr, t_point next, size_t y)
{

    char *dst;
    int img_y;
    int img_x;

    
    if (init_img_yx(ptr, next, &img_y, &img_x, y) == -1)
        return(rgb2int(ptr->parse.floor[0], ptr->parse.floor[1], ptr->parse.floor[2]));


    if (next.face == WHITE)
        dst = ptr->texture.no_img.addr + (img_y * ptr->texture.no_img.line_length + img_x * (ptr->texture.no_img.bits_per_pixel / 8));
    if (next.face == BLEU)
        dst = ptr->texture.so_img.addr + (img_y * ptr->texture.so_img.line_length + img_x * (ptr->texture.so_img.bits_per_pixel / 8));
    if (next.face == GREEN)
        dst = ptr->texture.we_img.addr + (img_y * ptr->texture.we_img.line_length + img_x * (ptr->texture.we_img.bits_per_pixel / 8));
    if (next.face == GRAY)
        dst = ptr->texture.ea_img.addr + (img_y * ptr->texture.ea_img.line_length + img_x * (ptr->texture.ea_img.bits_per_pixel / 8));
    return (*(int*)dst);
}



void    create_square(t_ptr *ptr, double ray_l, size_t x, t_point next)
{
    double  y;
    double  dy;
    int color;
    double  constss;

    ray_l =  (SCALE * HEIGHT) / ray_l;
    constss = scaleBetween(ptr->jump * ray_l, 0, 200, 0, WIDTH * HEIGHT);
    dy =  (WIDTH / 2 + constss) - (ray_l / 2);
    y = 0;

    while (y < dy)
    {
        my_mlx_pixel_put(&ptr->img3d, x, y, rgb2int(ptr->parse.ceiling[0], ptr->parse.ceiling[1], ptr->parse.ceiling[2]));
        y++;
    }

    next.ray_l = ray_l;
    next.first_point_in_wall = dy;
    while (y < (WIDTH / 2 + constss) + (ray_l / 2) && y < WIDTH)
    {
        color = GREEN;
        color = get_pixel_color(ptr, next, (size_t)y);

        if (!(color == -1 || x < 0 || x > HEIGHT || y < 0 || y > WIDTH))
            my_mlx_pixel_put(&ptr->img3d, x, y, color);
        y++;
    }

    while (y < WIDTH)
    {
        my_mlx_pixel_put(&ptr->img3d, x, y, rgb2int(ptr->parse.floor[0], ptr->parse.floor[1], ptr->parse.floor[2]));
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
