#include "cub3d.h"

int destroy_all(t_ptr *ptr)
{
    exit(0);
}
int handle_input(t_ptr *ptr)
{
    if (ptr->keys[W])
        go_up(ptr);
    if (ptr->keys[A])
        go_left(ptr);
    if (ptr->keys[S])
        go_down(ptr);
    if (ptr->keys[D])
        go_right(ptr);
    if (ptr->keys[R])
        right_angle(ptr);
    if (ptr->keys[L])
        left_argle(ptr);
    if (ptr->keys[E])
        destroy_all(ptr);
	return (0);
}

void	put_obunga_to_image(t_img_data *img, t_obunga obunga)
{
	double x;
	double y;
	double n;
	double x_max;
	double y_max;


	y = ((double)obunga.y / SCALE * DEBUG_SCALE) - SCALE_P;
	x_max = ((double)obunga.x / SCALE * DEBUG_SCALE) + SCALE_P;
	y_max = ((double)obunga.y / SCALE * DEBUG_SCALE) + SCALE_P;
	while (y <= y_max)
	{
		x = ((double)obunga.x / SCALE * DEBUG_SCALE) - SCALE_P;
		while (x <= x_max)
		{
			my_mlx_pixel_put(img, x, y, BLACK);
			x++;
		}
		y++;
	}
}

size_t scaleBetween(size_t unscaledNum, size_t minAllowed, size_t maxAllowed, size_t min, size_t max) {
  return (maxAllowed - minAllowed) * (unscaledNum - min) / (max - min) + minAllowed;
}

    // if (next.face == GREEN || next.face == GRAY)
    //     *img_x = (next.y - (long long)next.y / SCALE * SCALE) * w / SCALE;
    // else
    //     *img_x = (next.x - (long long)next.x / SCALE * SCALE) * w / SCALE;

    // *img_y = (y - next.first_point_in_wall) * (h / next.ray_l);



int get_obunga_color(t_ptr *ptr, size_t y, size_t x, size_t first_point_y, size_t first_point_x, size_t max_y, size_t max_x)
{
    char *dst;
    int img_y;
    int img_x;

    

    // img_y = ((y - first_point_y) * (ptr->obunga.img_w / SCALE));
    // img_x = ((x - first_point_x) * (ptr->obunga.img_h / SCALE));

    img_y = scaleBetween(y, 0, ptr->obunga.img_w, first_point_y, max_y);
    img_x = scaleBetween(x, 0, ptr->obunga.img_h, first_point_x, max_x);


    // if (init_img_yx(ptr, next, &img_y, &img_x, y) == -1)
    //     return(rgb2int(ptr->parse.floor[0], ptr->parse.floor[1], ptr->parse.floor[2]));


    dst = ptr->obunga.img.addr + (img_y * ptr->obunga.img.line_length + img_x * (ptr->obunga.img.bits_per_pixel / 8));

    // printf("%d\n", *(int*)dst);
    // exit(0);

    return (*(int*)dst);
}



void    put_obunga_to_img(t_ptr *ptr)
{
    int color ;
    if (ptr->obunga.dst == 0)
        return;
    size_t consts = (SCALE * WIDTH) / ptr->obunga.dst;
    size_t dst;
    // printf("%d\n", ptr->obunga.dst);

    size_t y;
    size_t x = ptr->obunga.img_x - consts;
    // size_t x = ptr->obunga.img_x - (SCALE * ptr->obunga.img_h) / ptr->obunga.dst;

    dst =  (SCALE * HEIGHT) / ptr->obunga.dst;

    while (x < ptr->obunga.img_x + consts)
    {
        y = WIDTH / 2 - dst / 2;
        while (y < (WIDTH / 2) + (dst) / 2 && y < WIDTH)
        {
            if (x < HEIGHT && x > 0 && y > 0 && y < WIDTH)
            {
                color = get_obunga_color(ptr, y, x, WIDTH / 2 - dst / 2, ptr->obunga.img_x - consts, (WIDTH / 2) + (dst) / 2 , ptr->obunga.img_x + consts);
                if (color >= 0)
                    my_mlx_pixel_put(&ptr->img3d, x, y, color);

            }
            y++;
        }
        x++;
    }
    
}

int render_loop(t_ptr *ptr)
{
    // printf("O:%f,%f\n", ptr->obunga.y, ptr->obunga.x);
    handle_input(ptr);
    if (DEBUG)
    {
        create_map(ptr);
        put_player_to_image(&ptr->win.img, ptr->player);
        put_obunga_to_image(&ptr->win.img, ptr->obunga);
        mlx_put_image_to_window(ptr->win.mlx, ptr->win.win, ptr->win.img.img, 0, 0);
    }
	put_arrow(ptr);
    put_obunga_to_img(ptr);
    mlx_put_image_to_window(ptr->win.mlx, ptr->win3d, ptr->img3d.img, 0, 0);
	return (0);
}

int main(int argc, char const **argv)
{
    t_ptr	ptr;

    ft_parse(&ptr, argc, argv);
	init_mlx(&ptr);

    mlx_loop_hook(ptr.win.mlx, render_loop, &ptr);
    // render_loop(&ptr);
    mlx_hook(ptr.win3d, DestroyNotify, ButtonPressMask, destroy_all, &ptr);
    mlx_hook(ptr.win3d, KeyPress, KeyPressMask, key_pressed, &ptr);
    mlx_hook(ptr.win3d, KeyRelease, KeyReleaseMask, key_released, &ptr);


	mlx_loop(ptr.win.mlx);
	return (0);
}
