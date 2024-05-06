#include "cub3d.h"

int key_pressed(int keycode, t_ptr *ptr) {
    if (keycode == XK_w)
        ptr->keys[W] = 1;
    if (keycode == XK_d)
        ptr->keys[D] = 1;
    if (keycode == XK_s)
        ptr->keys[S] = 1;
    if (keycode == XK_a)
        ptr->keys[A] = 1;
    if (keycode == XK_Left)
        ptr->keys[L] = 1;
    if (keycode == XK_Right)
        ptr->keys[R] = 1;
    if (keycode == XK_Escape)
        ptr->keys[E] = 1;
    
    return 0;
}

int key_released(int keycode, t_ptr *ptr) {
    if (keycode == XK_w)
        ptr->keys[W] = 0;
    if (keycode == XK_d)
        ptr->keys[D] = 0;
    if (keycode == XK_s)
        ptr->keys[S] = 0;
    if (keycode == XK_a)
        ptr->keys[A] = 0;
    if (keycode == XK_Left)
        ptr->keys[L] = 0;
    if (keycode == XK_Right)
        ptr->keys[R] = 0;
    if (keycode == XK_Escape)
        ptr->keys[E] = 0;
    return 0;
}

// int key_pressed(int keycode, t_ptr *ptr) {
//     if (keycode == W_M)
//         ptr->keys[W] = 1;
//     if (keycode == D_M)
//         ptr->keys[D] = 1;
//     if (keycode == S_M)
//         ptr->keys[S] = 1;
//     if (keycode == A_M)
//         ptr->keys[A] = 1;
//     if (keycode == LEFT_M)
//         ptr->keys[L] = 1;
//     if (keycode == RIGHT_M)
//         ptr->keys[R] = 1;
//     if (keycode == ESC_M)
//         ptr->keys[E] = 1;
    
//     return 0;
// }

// int key_released(int keycode, t_ptr *ptr) {
//     if (keycode == W_M)
//         ptr->keys[W] = 0;
//     if (keycode == D_M)
//         ptr->keys[D] = 0;
//     if (keycode == S_M)
//         ptr->keys[S] = 0;
//     if (keycode == A_M)
//         ptr->keys[A] = 0;
//     if (keycode == LEFT_M)
//         ptr->keys[L] = 0;
//     if (keycode == RIGHT_M)
//         ptr->keys[R] = 0;
//     if (keycode == ESC_M)
//         ptr->keys[E] = 0;
//     return 0;
// }



void go_up(t_ptr *ptr)
{
    long long y;
    long long x;
    
    y = sin(ptr->player.angle) * PLAYER_SPEED;
    x = cos(ptr->player.angle) * PLAYER_SPEED;
    if (ptr->map2d[(ptr->player.y + (y * SOME_SPACE)) / SCALE][(ptr->player.x) / SCALE] == '0')
        ptr->player.y +=  y;
    if (ptr->map2d[(ptr->player.y) / SCALE][(ptr->player.x + (x * SOME_SPACE)) / SCALE] == '0')
        ptr->player.x +=  x;

}

void go_right(t_ptr *ptr)
{
    long long y;
    long long x;

    y = sin(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
    x = cos(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
    if (ptr->map2d[(ptr->player.y + (y * SOME_SPACE)) / SCALE][(ptr->player.x) / SCALE] == '0')
        ptr->player.y +=  y;
    if (ptr->map2d[(ptr->player.y) / SCALE][(ptr->player.x + (x * SOME_SPACE)) / SCALE] == '0')
        ptr->player.x +=  x;
}

void go_down(t_ptr *ptr)
{
    long long y;
    long long x;

    y = sin(ptr->player.angle) * PLAYER_SPEED;
    x = cos(ptr->player.angle) * PLAYER_SPEED;


    // if (ptr->map2d[(ptr->player.y - y + 100) / SCALE][(ptr->player.x - x) / SCALE] == '0')
    //     return;
    // if (ptr->map2d[(ptr->player.y - y - 100) / SCALE][(ptr->player.x - x) / SCALE] == '0')
    //     return;
    // if (ptr->map2d[(ptr->player.y - y ) / SCALE][(ptr->player.x - x + 100) / SCALE] == '0')
    //     return;
    // if (ptr->map2d[(ptr->player.y - y ) / SCALE][(ptr->player.x - x - 100) / SCALE] == '0')
    //     return;


    if (ptr->map2d[(ptr->player.y) / SCALE][(ptr->player.x - (x * SOME_SPACE)) / SCALE] == '0')
        ptr->player.x -=  x;
    if (ptr->map2d[(ptr->player.y - (y * SOME_SPACE)) / SCALE][(ptr->player.x) / SCALE] == '0')
        ptr->player.y -=  y;
}

void go_left(t_ptr *ptr)
{
    long long y;
    long long x;

    y = sin(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
    x = cos(ptr->player.angle + NINETY_DEGREE) * PLAYER_SPEED;
    if (ptr->map2d[(ptr->player.y) / SCALE][(ptr->player.x - (x * SOME_SPACE)) / SCALE] == '0')
        ptr->player.x -=  x;
    if (ptr->map2d[(ptr->player.y - (y * SOME_SPACE)) / SCALE][(ptr->player.x) / SCALE] == '0')
        ptr->player.y -=  y;
}

void right_angle(t_ptr *ptr)
{
    ptr->player.angle += ROTATION_SPEED;
    if (ptr->player.angle > RAD)
        ptr->player.angle = 0;
}

void left_argle(t_ptr *ptr)
{
    ptr->player.angle -= ROTATION_SPEED;
    if (ptr->player.angle < 0)
        ptr->player.angle = RAD;
}
