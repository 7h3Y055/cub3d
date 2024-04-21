#include "cub3d.h"

int main(int argc, char const **argv)
{
    t_ptr ptr;


    ft_parse(&ptr, argc, argv);

    // printf("no: %s\n", ptr.parse.no);
    // printf("so: %s\n", ptr.parse.so);
    // printf("wo: %s\n", ptr.parse.we);
    // printf("eo: %s\n", ptr.parse.ee);

    // printf("floor array: ");
    // printf("%d,", ptr.parse.floor[0]);
    // printf("%d,", ptr.parse.floor[1]);
    // printf("%d\n", ptr.parse.floor[2]);

    // printf("ceiling array: ");
    // printf("%d,", ptr.parse.ceiling[0]);
    // printf("%d,", ptr.parse.ceiling[1]);
    // printf("%d\n", ptr.parse.ceiling[2]);

    printf("map2d:\n");
    for (int i = 0; i < ptr.parse.x; i++) {
        for (int j = 0; j < ptr.parse.x; j++) {
            printf("%d ", ptr.parse.map2d[i][j]);
        }
        printf("\n");
    }

}
