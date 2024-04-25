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
	else if (map_unit == 'N')
		return (0xFE2D00);
	else
		return (0xffffff);
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
	create_map(&ptr.win.img, ptr.map2d_scaled); //bdl ptr.map2d b scaled
	ptr.win.win = mlx_new_window(ptr.win.mlx, HEIGHT, WIDTH, "C");
	mlx_put_image_to_window(ptr.win.mlx, ptr.win.win, ptr.win.img.img, 5, 5);
	mlx_loop(ptr.win.mlx);

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

}
