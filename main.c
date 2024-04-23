#include "cub3d.h"

int main(int argc, char const **argv)
{
    t_ptr ptr;

    ft_parse(&ptr, argc, argv);

    printf("valid map\n");

    test(&ptr);

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
    // for (int i = 0; ptr.map2d[i]; i++) {
    //     printf("%s\n", ptr.map2d[i]);
    // }

}
