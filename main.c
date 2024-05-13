#include "cub3d.h"

int destroy_all(t_ptr *ptr)
{
    exit(0);
}

void    jump(t_ptr *ptr)
{
    if (ptr->keys[ES])
    {
        if (ptr->jumps.jump_stats < ptr->jumps.jump_hight)
        {
            ptr->jumps.jump_stats += ptr->jumps.jump_speedup;
            ptr->jumps.jump_speedup -= 10;
        }
        else
            ptr->keys[ES] = 0; 
    }
    else
    {
        if (ptr->jumps.jump_stats > 0)
            ptr->jumps.jump_stats -= ptr->jumps.jump_speeddown;
        else
            jump_init(ptr);
    }
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
    jump(ptr);
    if (ptr->keys[9] && ptr->updown < 300)
		ptr->updown += 10;
    if (ptr->keys[10] && ptr->updown >= -300)
		ptr->updown -= 10;
	return (0);
}

// void	put_obunga_to_image(t_img_data *img, t_obunga obunga)
// {
// 	double x;
// 	double y;
// 	double n;
// 	double x_max;
// 	double y_max;


// 	y = ((double)obunga.y / SCALE * DEBUG_SCALE) - SCALE_P;
// 	x_max = ((double)obunga.x / SCALE * DEBUG_SCALE) + SCALE_P;
// 	y_max = ((double)obunga.y / SCALE * DEBUG_SCALE) + SCALE_P;
// 	while (y <= y_max)
// 	{
// 		x = ((double)obunga.x / SCALE * DEBUG_SCALE) - SCALE_P;
// 		while (x <= x_max)
// 		{
// 			my_mlx_pixel_put(img, x, y, BLACK);
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
    int color;
    int y;
    int x;
    int consts;
    int dst;

    if (ptr->obunga.dst == 0)
        return;
    consts = (SCALE * WIDTH) / ptr->obunga.dst;
    dst =  (SCALE * HEIGHT) / ptr->obunga.dst;
    ptr->jumps.consts = scaleBetween(ptr->jumps.jump_stats * dst, 0, 200, 0, WIDTH * HEIGHT) +  + ptr->updown;
    x = ptr->obunga.img_x - consts;
    while (x < (int)ptr->obunga.img_x + consts)
    {
        y = WIDTH / 2 + ptr->jumps.consts - dst / 2;
        while (y < (WIDTH / 2 + ptr->jumps.consts) + (dst) / 2 && y < WIDTH)
        {
            if (x < HEIGHT && x > 0 && y > 0 && y < WIDTH)
            {
                color = get_obunga_color(ptr, y - ptr->jumps.consts, x, WIDTH / 2 - dst / 2, ptr->obunga.img_x - consts, (WIDTH / 2) + (dst) / 2 , ptr->obunga.img_x + consts);
                if (color >= 0)
                    my_mlx_pixel_put(&ptr->img3d, x, y, color);

            }
            y++;
        }
        x++;
    }
}

int check_wall_obunga(t_ptr *ptr, size_t n)
{
    double y;
    double x;

    x = ptr->obunga.x + -cos(ptr->obunga.angle) * n;
    y = ptr->obunga.y + -sin(ptr->obunga.angle) * n;
    if (ptr->map2d[(long long)(y / SCALE)][(long long)(x / SCALE)] == '1')
        return (1);
    x = ptr->obunga.x + -cos(ptr->obunga.angle + 0.2) * n;
    y = ptr->obunga.y + -sin(ptr->obunga.angle + 0.2) * n;
    if (ptr->map2d[(long long)(y / SCALE)][(long long)(x / SCALE)] == '1')
        return (1);
    x = ptr->obunga.x + -cos(ptr->obunga.angle - 0.2) * n;
    y = ptr->obunga.y + -sin(ptr->obunga.angle - 0.2) * n;
    if (ptr->map2d[(long long)(y / SCALE)][(long long)(x / SCALE)] == '1')
        return (1);
    return (0);
}

void check_player_death(t_ptr *ptr)
{
    size_t n;

    if (distance(*ptr, ptr->flgas.tmp, 1) < SCALE)
    {
        n = 0;
        while (n < distance(*ptr, ptr->flgas.tmp, 1))
        {
            if (check_wall_obunga(ptr, n))
                return ;
            n++;
        }        
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
    if (ptr->map2d[((int)ptr->obunga.y) / SCALE][((int)ptr->obunga.x + (x * ENEMY_SPACE)) / SCALE] == '0' || ptr->map2d[((int)ptr->obunga.y) / SCALE][((int)ptr->obunga.x + (x * ENEMY_SPACE)) / SCALE] == 'O')
        ptr->obunga.x +=  x;
}


void    move_angle_with_mouse(t_ptr *ptr)
{
    int y;
    int x;
    static int last_px = HEIGHT / 2;
    static int last_py = WIDTH / 2;
    int ax;
    int ay;

    mlx_mouse_get_pos(ptr->win.mlx, ptr->win3d, &x, &y);
    ax = abs(x -  last_px);
    ay = abs(y -  last_py);
    if (x > last_px)
        ptr->player.angle += PI * (ax - 0) / (HEIGHT - 0) + 0;
    else
        ptr->player.angle -= PI * (ax - 0) / (HEIGHT - 0) + 0;

    if (y > last_py) // DOWN
    {
        if (ptr->updown + ay > -300)
        {
            ptr->updown -= ay;
        }
    }
    else // UP
    {
        if (ptr->updown - ay <= 300)
            ptr->updown += ay;
    }
        
    last_px = x;
    last_py = y;

}

void    put_minimap(t_ptr *ptr)
{
    int	x;
	int	y;
    int	x_map = ((int)ptr->player.x / SCALE) * MAP_SCALE - MAP_H / 2;
	int	y_map = ((double)ptr->player.y / SCALE) * MAP_SCALE - MAP_W / 2;

    ft_bzero(ptr->minimap.addr, MAP_H * MAP_W * ptr->minimap.bits_per_pixel / 8);
	y = 0;
	while (y < MAP_W)
	{
		x = 0;
		while (x < MAP_H)
		{
            if (x + x_map >=  0 && x + x_map < ptr->parse.x * MAP_SCALE
                && y + y_map >= 0 && y + y_map < ptr->parse.y * MAP_SCALE)
            {
                if ((x + x_map) % MAP_SCALE != 0 && (y + y_map) % MAP_SCALE != 0)
                    my_mlx_pixel_put(&ptr->minimap, x, y
                        , color_unit_pixel(ptr->map2d[(y + y_map) / MAP_SCALE][(x + x_map) / MAP_SCALE]));
                else
                    my_mlx_pixel_put(&ptr->minimap, x, y, GRAY);
            }
            else
                my_mlx_pixel_put(&ptr->minimap, x, y, BLACK);
			x++;
		}
		y++;
	}
    //put player
    my_mlx_pixel_put(&ptr->minimap, (double)ptr->player.x / SCALE * MAP_SCALE - x_map
        ,(double)ptr->player.y / SCALE * MAP_SCALE - y_map, RED);
    {
        double x;
        double y;
        double n;
        double x_max;
        double y_max;


        y = (double)ptr->player.y / SCALE * MAP_SCALE - y_map - SCALE_P;
        x_max = (double)ptr->player.x / SCALE * MAP_SCALE - x_map + SCALE_P;
        y_max = (double)ptr->player.y / SCALE * MAP_SCALE - y_map + SCALE_P;
        while (y < y_max)
        {
            x = (double)ptr->player.x / SCALE * MAP_SCALE - x_map - SCALE_P;
            while (x < x_max)
            {
                my_mlx_pixel_put(&ptr->minimap, x, y, RED);
                x++;
            }
            y++;
        }

    }
    //put arrow
    int n = 1;
	while (n < 20)
	{
		my_mlx_pixel_put(&ptr->minimap, ((double)ptr->player.x / SCALE * MAP_SCALE - x_map) + (cos((double)ptr->player.angle) * n)
            , ((double)(double)ptr->player.y / SCALE * MAP_SCALE - y_map) + (sin((double)ptr->player.angle) * n), RED);
		n++;
	}
    mlx_put_image_to_window(ptr->win.mlx, ptr->win3d, ptr->minimap.img, 5, 5);
}

int render_loop(t_ptr *ptr)
{
    handle_input(ptr);
	put_arrow(ptr);
    put_rays(ptr);
    obunga_move(ptr);
    move_angle_with_mouse(ptr);
    mlx_put_image_to_window(ptr->win.mlx, ptr->win3d, ptr->img3d.img, 0, 0);
    put_minimap(ptr);
    check_player_death(ptr);
	return (0);
}


int main(int argc, char const **argv)
{
    t_ptr	ptr;

    ft_parse(&ptr, argc, argv);

	init_mlx(&ptr);

    
    mlx_loop_hook(ptr.win.mlx, render_loop, &ptr);
    mlx_hook(ptr.win3d, DestroyNotify, ButtonPressMask, destroy_all, &ptr);
    mlx_hook(ptr.win3d, KeyPress, KeyPressMask, key_pressed, &ptr);
    mlx_hook(ptr.win3d, KeyRelease, KeyReleaseMask, key_released, &ptr);


	mlx_loop(ptr.win.mlx);
	return (0);
}
