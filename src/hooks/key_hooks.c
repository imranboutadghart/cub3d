# include "cube.h"

static void	press_key(int keycode, t_data *data);
static void	unpress_key(int keycode, t_data *data);

int key_press(int keycode, t_data *data)
{
	static int state = 0;
	if (keycode == KEY_ESC)
		close_all(data);
	if (keycode == KEY_SPACE)
	{
		if (!state)
			mlx_loop_hook(data->mlx.mlx, game_pause, data);
		else
			mlx_loop_hook(data->mlx.mlx, game_loop, data);
		state = !state;
	}
	press_key(keycode, data);
	return (0);
}

int	key_release(int	keycode, t_data *data)
{
	unpress_key(keycode, data);
	return (0);
}

void	press_key(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
		data->pressed_keys[UP_PRESSED] = 1;
	else if (keycode == KEY_DOWN)
		data->pressed_keys[DOWN_PRESSED] = 1;
	else if (keycode == KEY_LEFT)
		data->pressed_keys[LEFT_PRESSED] = 1;
	else if (keycode == KEY_RIGHT)
		data->pressed_keys[RIGHT_PRESSED] = 1;
	else if (keycode == KEY_W)
		data->pressed_keys[W_PRESSED] = 1;
	else if (keycode == KEY_A)
		data->pressed_keys[A_PRESSED] = 1;
	else if (keycode == KEY_S)
		data->pressed_keys[S_PRESSED] = 1;
	else if (keycode == KEY_D)
		data->pressed_keys[D_PRESSED] = 1;
	
}

void	unpress_key(int keycode, t_data *data)
{
	if (keycode == KEY_UP)
		data->pressed_keys[UP_PRESSED] = 0;
	else if (keycode == KEY_DOWN)
		data->pressed_keys[DOWN_PRESSED] = 0;
	else if (keycode == KEY_LEFT)
		data->pressed_keys[LEFT_PRESSED] = 0;
	else if (keycode == KEY_RIGHT)
		data->pressed_keys[RIGHT_PRESSED] = 0;
	else if (keycode == KEY_W)
		data->pressed_keys[W_PRESSED] = 0;
	else if (keycode == KEY_A)
		data->pressed_keys[A_PRESSED] = 0;
	else if (keycode == KEY_S)
		data->pressed_keys[S_PRESSED] = 0;
	else if (keycode == KEY_D)
		data->pressed_keys[D_PRESSED] = 0;
}