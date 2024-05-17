// int	key_pressed(int keycode, t_ptr *ptr)
// {
// 	if (keycode == W_M)
// 		ptr->keys[W] = 1;
// 	if (keycode == D_M)
// 		ptr->keys[D] = 1;
// 	if (keycode == S_M)
// 		ptr->keys[S] = 1;
// 	if (keycode == A_M)
// 		ptr->keys[A] = 1;
// 	if (keycode == LEFT_M)
// 		ptr->keys[L] = 1;
// 	if (keycode == RIGHT_M)
// 		ptr->keys[R] = 1;
// 	if (keycode == F_M)
// 		ptr->keys[O] = 1;
// 	if (keycode == ESP_M && ptr->jumps.jump_stats == 0)
// 		ptr->keys[ES] = 1;
// 	if (keycode == UP_M)
// 		ptr->keys[9] = 1;
// 	if (keycode == DOWN_M)
// 		ptr->keys[10] = 1;
// 	if (keycode == ESC_M)
// 		destroy_all(ptr);
// 	return (0);
// }

// int	key_released(int keycode, t_ptr *ptr)
// {
// 	if (keycode == W_M)
// 		ptr->keys[W] = 0;
// 	if (keycode == D_M)
// 		ptr->keys[D] = 0;
// 	if (keycode == S_M)
// 		ptr->keys[S] = 0;
// 	if (keycode == A_M)
// 		ptr->keys[A] = 0;
// 	if (keycode == LEFT_M)
// 		ptr->keys[L] = 0;
// 	if (keycode == RIGHT_M)
// 		ptr->keys[R] = 0;
// 	if (keycode == F_M)
// 		ptr->keys[O] = 0;
// 	if (keycode == UP_M)
// 		ptr->keys[9] = 0;
// 	if (keycode == DOWN_M)
// 		ptr->keys[10] = 0;
// 	return (0);
// }