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

int render_loop(t_ptr *ptr)
{
	ft_bzero(ptr->img3d.addr, WIDTH * HEIGHT * (ptr->img3d.bits_per_pixel / 8));

    handle_input(ptr);
	// create_map(ptr);
	put_arrow(ptr);

	// put_player_to_image(&ptr->win.img, ptr->player);
	// mlx_put_image_to_window(ptr->win.mlx, ptr->win.win, ptr->win.img.img, 0, 0);
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
