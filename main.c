#include "cub3d.h"

void	my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	color_unit_pixel(char map_unit)
{
	if (map_unit == '1')
		return (0x002177);
	else if (map_unit == '0')
		return (0xffffff);
	else
		return (0);
}

void	create_map(t_img_data *img, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			my_mlx_pixel_put(img, x, y, color_unit_pixel(map[y][x]));
			x++;
		}
		y++;
	}
}

void	put_player_to_image(t_img_data *img, t_player player)
{
	size_t x;
	size_t y;
	size_t x_max;
	size_t y_max;

	y = player.y - SCALE_P;
	x_max = player.x + SCALE_P;
	y_max = player.y + SCALE_P;
	while (y <= y_max)
	{
		x = player.x - SCALE_P;
		while (x <= x_max)
		{
			my_mlx_pixel_put(img, x, y, 0xFE2D00);
			x++;
		}
		y++;
	}
}

int main(int argc, char const **argv)
{
    t_ptr ptr;
    int i;
    int j;

    ft_parse(&ptr, argc, argv);

    printf("valid map\n");

    ptr.win.mlx = mlx_init();
	ptr.win.img.img = mlx_new_image(ptr.win.mlx, ptr.parse.x * SCALE, ptr.parse.y * SCALE);
	ptr.win.img.addr = mlx_get_data_addr(ptr.win.img.img, &ptr.win.img.bits_per_pixel, &ptr.win.img.line_length,
				&ptr.win.img.endian);
	create_map(&ptr.win.img, ptr.map2d_scaled);
	put_player_to_image(&ptr.win.img, ptr.player);
	ptr.win.win = mlx_new_window(ptr.win.mlx, ptr.parse.x * SCALE, ptr.parse.y * SCALE, "Cub3D");
	mlx_put_image_to_window(ptr.win.mlx, ptr.win.win, ptr.win.img.img, 0, 0);
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

    // printf("\n");

    // printf("player position:\n");
    // printf("y:%d\n", ptr.player.y);
    // printf("x:%d\n", ptr.player.x);
    // printf("A:%f\n", ptr.player.angle);
    // printf("map2d_scaled:\n");
    // printf("y:%d\n", ptr.parse.y * SCALE);
    // printf("x:%d\n", ptr.parse.x * SCALE);
    // printf("\n");
    // i = 0;
    // while (i < ptr.parse.y * SCALE)
    // {
    //     j = 0;
    //     while (j < ptr.parse.x * SCALE)
    //     {
    //         printf("%c", ptr.map2d_scaled[i][j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i++;
    // }