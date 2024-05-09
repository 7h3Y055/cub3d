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

void    put_obunga_to_img(t_ptr *ptr)
{
    printf("%d\n", ptr->obunga.dst);
    if (ptr->obunga.dst == 0)
        return;

    size_t y;
    size_t x = ptr->obunga.img_x;

    ptr->obunga.dst =  (SCALE * HEIGHT) / ptr->obunga.dst;

    y = WIDTH / 2 - ptr->obunga.dst / 2;
    while (y < (WIDTH / 2) + (ptr->obunga.dst) / 2 && y < WIDTH)
    {
        my_mlx_pixel_put(&ptr->img3d, x, y, BLACK);
        my_mlx_pixel_put(&ptr->img3d, x, y + 1, BLACK);
        my_mlx_pixel_put(&ptr->img3d, x, y - 1, BLACK);
        my_mlx_pixel_put(&ptr->img3d, x + 1, y, BLACK);
        my_mlx_pixel_put(&ptr->img3d, x - 1, y, BLACK);
        y++;
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
