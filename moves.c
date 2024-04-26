#include "cub3d.h"


void go_up(t_ptr *ptr)
{
    long long y;
    long long x;

    y = sin(ptr->player.angle) * PLAYER_SPEED;
    x = cos(ptr->player.angle) * PLAYER_SPEED;
    if (ptr->map2d_scaled[ptr->player.y +  y][ptr->player.x +  x] == '0')
    {
        ptr->player.x +=  x;
        ptr->player.y +=  y;
    }
    else
        printf("REFUSE!\n");

}

void go_right(t_ptr *ptr)
{
    long long y;
    long long x;

    y = sin(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
    x = cos(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
    if (ptr->map2d_scaled[ptr->player.y +  y][ptr->player.x +  x] == '0')
    {
        ptr->player.x +=  x;
        ptr->player.y +=  y;
    }
    else
        printf("REFUSE!\n");
}

void go_down(t_ptr *ptr)
{
    long long y;
    long long x;

    y = sin(ptr->player.angle) * PLAYER_SPEED;
    x = cos(ptr->player.angle) * PLAYER_SPEED;
    if (ptr->map2d_scaled[ptr->player.y -  y][ptr->player.x -  x] == '0')
    {
        ptr->player.x -=  x;
        ptr->player.y -=  y;
    }
    else
        printf("REFUSE!\n");
}

void go_left(t_ptr *ptr)
{
    long long y;
    long long x;

    y = sin(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
    x = cos(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
    if (ptr->map2d_scaled[ptr->player.y -  y][ptr->player.x -  x] == '0')
    {
        ptr->player.x -=  x;
        ptr->player.y -=  y;
    }
    else
        printf("REFUSE!\n");
}

void right_angle(t_ptr *ptr)
{
    ptr->player.angle += 0.1;
    if (ptr->player.angle > RAD)
        ptr->player.angle = 0;
    // printf("[%f]\n", ptr->player.angle);
}

void left_argle(t_ptr *ptr)
{
    ptr->player.angle -= 0.1;
    if (ptr->player.angle < 0)
        ptr->player.angle = RAD;
    // printf("[%f]\n", ptr->player.angle);
}
