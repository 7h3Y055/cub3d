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
    if (ptr->keys[7])
    {
        if (ptr->jump < 200)
            ptr->jump += 30;
        else
            ptr->keys[7] = 0;
    }
    else
    {
        if (ptr->jump > 0)
            ptr->jump -= 30;
    }
	return (0);
}

void    put_obunga(t_ptr *ptr)
{
    size_t  i = 0;
    size_t  x,y;

    
}

// int    check_enemy(t_ptr *ptr)
// {
//     double  enemy_angle;

//     enemy_angle = 
// }

int render_loop(t_ptr *ptr)
{
    handle_input(ptr);
    if (DEBUG)
    {
        create_map(ptr);
        put_player_to_image(&ptr->win.img, ptr->player);
        put_player_to_image(&ptr->win.img, ptr->player);
        mlx_put_image_to_window(ptr->win.mlx, ptr->win.win, ptr->win.img.img, 0, 0);
    }
	put_arrow(ptr);
    mlx_put_image_to_window(ptr->win.mlx, ptr->win3d, ptr->img3d.img, 0, 0);
    ft_bzero(ptr->img3d.addr, WIDTH * HEIGHT * (ptr->img3d.bits_per_pixel / 8));
	return (0);
}

int main(int argc, char const **argv)
{
    t_ptr	ptr;

    ft_bzero(&ptr, sizeof(ptr));
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
