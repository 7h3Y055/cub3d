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
}


int render_loop(t_ptr *ptr)
{
    handle_input(ptr);
	create_map(&ptr->win.img, ptr->map2d_scaled);
	put_player_to_image(&ptr->win.img, ptr->player);
	mlx_put_image_to_window(ptr->win.mlx, ptr->win.win, ptr->win.img.img, 0, 0);

}

int main(int argc, char const **argv)
{
    t_ptr ptr;
    int i;
    int j;

    ft_parse(&ptr, argc, argv);



    printf("valid map\n");
    ptr.win.mlx = mlx_init();
	ptr.win.win = mlx_new_window(ptr.win.mlx, ptr.parse.x * SCALE, ptr.parse.y * SCALE, "Cub3D");

	ptr.win.img.img = mlx_new_image(ptr.win.mlx, ptr.parse.x * SCALE, ptr.parse.y * SCALE);
	ptr.win.img.addr = mlx_get_data_addr(ptr.win.img.img, &ptr.win.img.bits_per_pixel, &ptr.win.img.line_length,
				&ptr.win.img.endian);

    mlx_loop_hook(ptr.win.mlx, render_loop, &ptr);


    mlx_hook(ptr.win.win, DestroyNotify, ButtonPressMask, destroy_all, &ptr);

    mlx_hook(ptr.win.win, KeyPress, KeyPressMask, key_pressed, &ptr);
    mlx_hook(ptr.win.win, KeyRelease, KeyReleaseMask, key_released, &ptr);

	mlx_loop(ptr.win.mlx);
}
