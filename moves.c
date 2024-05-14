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
    if (keycode == XK_f)
        ptr->keys[O] = 1;
    if (keycode == XK_space && ptr->jumps.jump_stats == 0)
        ptr->keys[ES] = 1;
    if (keycode == XK_Up)
        ptr->keys[9] = 1;
    if (keycode == XK_Down)
        ptr->keys[10] = 1;
    if (keycode == XK_Escape)
        destroy_all(ptr);

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
    if (keycode == XK_f)
        ptr->keys[O] = 0;
    if (keycode == XK_Up)
        ptr->keys[9] = 0;
    if (keycode == XK_Down)
        ptr->keys[10] = 0;
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
//     if (keycode == F_M)
//         ptr->keys[O] = 1;
//     if (keycode == ESP_M && ptr->jumps.jump_stats == 0)
//         ptr->keys[ES] = 1;
//     if (keycode == UP_M)
//         ptr->keys[9] = 1;
//     if (keycode == DOWN_M)
//         ptr->keys[10] = 1;
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
//     if (keycode == F_M)
//         ptr->keys[O] = 0;
//     if (keycode == UP_M)
//         ptr->keys[9] = 0;
//     if (keycode == DOWN_M)
//         ptr->keys[10] = 0;
//     return 0;
// }

void check_player_move(t_ptr *ptr, long long y, long long x)
{
    if (ptr->map2d[(ptr->player.y) / SCALE][(ptr->player.x + (x * PLAYER_SPACE)) / SCALE] == '0' || ptr->map2d[(ptr->player.y) / SCALE][(ptr->player.x + (x * PLAYER_SPACE)) / SCALE] == 'O')
        ptr->player.x += x;
    if (ptr->map2d[(ptr->player.y + (y * PLAYER_SPACE)) / SCALE][(ptr->player.x) / SCALE] == '0' || ptr->map2d[(ptr->player.y + (y * PLAYER_SPACE)) / SCALE][(ptr->player.x) / SCALE] == 'O')
        ptr->player.y += y;
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
