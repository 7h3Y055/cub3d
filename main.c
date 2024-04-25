#include "cub3d.h"

int main(int argc, char const **argv)
{
    t_ptr ptr;
    int i;
    int j;

    ft_parse(&ptr, argc, argv);

    printf("valid map\n");

    

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
