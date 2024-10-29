# include "cube.h"

int key_press(int keycode, t_data *data)
{
	static int state = 0;
	printf("key pressed : %d\n", keycode);
	if (keycode == KEY_ESC)
		close_win(data);
	if (keycode == KEY_SPACE)
	{
		if (!state)
			mlx_loop_hook(data->mlx.mlx, game_pause, data);
		else
			mlx_loop_hook(data->mlx.mlx, game_loop, data);
		state = !state;
	}
	if (keycode == KEY_UP)
		data->player.y -= data->player.walk_speed;
	if (keycode == KEY_DOWN)
		data->player.y += data->player.walk_speed;
	if (keycode == KEY_LEFT)
		data->player.x -= data->player.walk_speed;
	if (keycode == KEY_RIGHT)
		data->player.x += data->player.walk_speed;
	return (0);
}