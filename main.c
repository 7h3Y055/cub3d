#include "cub3d.h"



int destroy_all(t_ptr *ptr)
{
    exit(0);
}
int handle_input(int key, void *ptr)
{
    // printf("%d\n", key);
    if (key == W)
        go_up(ptr);
    else if (key == A)
        go_left(ptr);
    else if (key == S)
        go_down(ptr);
    else if (key == D)
        go_right(ptr);
    else if (key == RIGHT)
        right_angle(ptr);
    else if (key == LEFT)
        left_argle(ptr);
    else if (key == ESC)
        destroy_all(ptr);
}


int render_loop(t_ptr *ptr)
{
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
    mlx_hook(ptr.win.win, 2, 1L<<0, handle_input, &ptr);
    mlx_key_hook(ptr.win.win, handle_input, &ptr);
	mlx_loop(ptr.win.mlx);
}

    // printf("no: %s\n", ptr.parse.no);
    // printf("so: %s\n", ptr.parse.so);
    // printf("wo: %s\n", ptr.parse.we);
    // printf("ea: %s\n", ptr.parse.ea);
    // printf("\n");

    // printf("floor array: ");
    // printf("%d,", ptr.parse.floor[0]);
    // printf("%d,", ptr.parse.floor[1]);
    // printf("%d\n", ptr.parse.floor[2]);

    // printf("ceiling array: ");
    // printf("%d,", ptr.parse.ceiling[0]);
    // printf("%d,", ptr.parse.ceiling[1]);
    // printf("%d\n", ptr.parse.ceiling[2]);

    // printf("\n");
    // printf("map2d:\n");
    // printf("y:%d\n", ptr.parse.y);
    // printf("x:%d\n", ptr.parse.x);
    // printf("\n");

    // i = 0;
    // while (ptr.map2d[i])
    // {
    //     j = 0;
    //     while (ptr.map2d[i][j])
    //     {
    //         printf("%c", ptr.map2d[i][j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }

//     printf("\n");

//     printf("player position:\n");
//     printf("y:%d\n", ptr.player.y);
//     printf("x:%d\n", ptr.player.x);
//     printf("A:%f\n", ptr.player.angle);
//     printf("map2d_scaled:\n");
//     printf("y:%d\n", ptr.parse.y * SCALE);
//     printf("x:%d\n", ptr.parse.x * SCALE);
//     printf("\n");
//     i = 0;
//     while (i < ptr.parse.y * SCALE)
//     {
//         j = 0;
//         while (j < ptr.parse.x * SCALE)
//         {
//             printf("%c", ptr.map2d_scaled[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
// }