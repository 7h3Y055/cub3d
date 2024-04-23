#include "cub3d.h"

int ft_close(int flag, void *a)
{
    exit(0);
}

char **ft_init_scaled_map(t_ptr *ptr)
{
    ptr->map2d = allocate_memory_for_map2d(ptr, ptr->parse.y * SCALE, ptr->parse.y * SCALE);
    //init_scaled map 
}

void    test(t_ptr *ptr)
{
    // ptr->win.mlx = mlx_init();
    // ptr->win.win = mlx_new_window(ptr->win.mlx, 1280,720, "test");

    ft_init_scaled_map(ptr);
    
	// mlx_key_hook(ptr->win.win, ft_close, &ptr);
    // mlx_loop(ptr->win.mlx);

    // mlx_destroy_window(ptr->win.mlx, ptr->win.win);
    // mlx_destroy_display(ptr->win.mlx);
    // free(ptr->win.mlx);
}