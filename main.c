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
    // if (ptr->keys[E])
    // {
    //     if (ptr->jump < 1500)
    //         ptr->jump += 200;
    //     else
    //         ptr->keys[7] = 0; 
    // }
    // else
    // {
    //     if (ptr->jump > 0)
    //         ptr->jump -= 100;
    //     else
    //         ptr->jump = 0;
    // }
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

int get_obunga_color(t_ptr *ptr, size_t y, size_t x, size_t first_point_y, size_t first_point_x, size_t max_y, size_t max_x)
{
    char *dst;
    int img_y;
    int img_x;

    static int n;
    

    // img_y = ((y - first_point_y) * (ptr->obunga.img_w / SCALE));
    // img_x = ((x - first_point_x) * (ptr->obunga.img_h / SCALE));

    img_y = scaleBetween(y, 0, ptr->obunga.img_w, first_point_y, max_y);
    img_x = scaleBetween(x, 0, ptr->obunga.img_h, first_point_x, max_x);


    // if (n == 1 && img_x == 0 && img_y == 0)
    //     return -1;
    // if (img_x == 0 && img_y == 0)
    // {
    //     printf("%d %d\n", y == first_point_y, x == first_point_x);
    // }
    // return(rgb2int(ptr->parse.floor[0], ptr->parse.floor[1], ptr->parse.floor[2]));

    dst = ptr->obunga.img.addr + (img_y * ptr->obunga.img.line_length + img_x * (ptr->obunga.img.bits_per_pixel / 8));

    // printf("%d\n", *(int*)dst);
    // exit(0);

    return (*(int*)dst);
}

void    put_obunga_to_img(t_ptr *ptr)
{
    int color ;
    int y;
    int x;
    int consts;
    int dst;
    double constss;

    if (ptr->obunga.dst == 0)
        return;
    consts = (SCALE * WIDTH) / ptr->obunga.dst;
    dst =  (SCALE * HEIGHT) / ptr->obunga.dst;
    constss = scaleBetween(ptr->jump * dst, 0, 200, 0, WIDTH * HEIGHT);
    x = ptr->obunga.img_x - consts;
    while (x < (int)ptr->obunga.img_x + consts)
    {
        y = WIDTH / 2 + constss - dst / 2;
        while (y < (WIDTH / 2 + constss) + (dst) / 2 && y < WIDTH)
        {
            if (x < HEIGHT && x > 0 && y > 0 && y < WIDTH)
            {
                color = get_obunga_color(ptr, y - constss, x, WIDTH / 2 - dst / 2, ptr->obunga.img_x - consts, (WIDTH / 2) + (dst) / 2 , ptr->obunga.img_x + consts);
                if (color >= 0)
                    my_mlx_pixel_put(&ptr->img3d, x, y, color);

            }
            y++;
        }
        x++;
    }
    // exit(0);
}

void check_player_death(t_ptr *ptr)
{
    if (distance(*ptr, ptr->flgas.tmp, 1) < SCALE)
    {
        exit(ft_error(ptr, "DEATH!\n", 0));
    }
}

void obunga_move(t_ptr *ptr)
{
    long long y;
    long long x;
    
    y = -sin(ptr->obunga.angle) * ENEMY_SPEED;
    x = -cos(ptr->obunga.angle) * ENEMY_SPEED;
    if (ptr->map2d[((int)ptr->obunga.y + (y * ENEMY_SPACE)) / SCALE][((int)ptr->obunga.x) / SCALE] == '0' || ptr->map2d[((int)ptr->obunga.y + (y * ENEMY_SPACE)) / SCALE][((int)ptr->obunga.x) / SCALE] == 'O')
        ptr->obunga.y +=  y;
    if (ptr->map2d[((int)ptr->obunga.y) / SCALE][((int)ptr->obunga.x + (x * ENEMY_SPACE)) / SCALE] == '0' || ptr->map2d[((int)ptr->obunga.y) / SCALE][((int)ptr->obunga.x + (x * ENEMY_SPACE)) / SCALE] == '0')
        ptr->obunga.x +=  x;
}


void    move_angle_with_mouse(t_ptr *ptr)
{
    int y;
    int x;
    static int last_p = HEIGHT / 2;
    double n;

    mlx_mouse_get_pos(ptr->win.mlx, ptr->win3d, &x, &y);
    n = abs(x -  last_p);
    if (x > last_p)
        ptr->player.angle += PI * (n - 0) / (HEIGHT - 0) + 0;
    else
        ptr->player.angle -= PI * (n - 0) / (HEIGHT - 0) + 0;
    last_p = x;

}


int render_loop(t_ptr *ptr)
{
    handle_input(ptr);
    if (DEBUG)
    {
        create_map(ptr);
        put_player_to_image(&ptr->win.img, ptr->player);
        // put_obunga_to_image(&ptr->win.img, ptr->obunga);
        mlx_put_image_to_window(ptr->win.mlx, ptr->win.win, ptr->win.img.img, 0, 0);
    }
	put_arrow(ptr);
    put_rays(ptr);
    obunga_move(ptr);
    move_angle_with_mouse(ptr);
    check_player_death(ptr);
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
