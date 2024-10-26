# include "cube.h"

int key_press(int keycode, t_data *data)
{
	static int state = 0;
	printf("key pressed : %d\n", keycode);
	if (keycode == 65307)
		close_win(data);
	if (keycode == 32)
	{
		if (!state)
			mlx_loop_hook(data->mlx.mlx, game_pause, data);
		else
			mlx_loop_hook(data->mlx.mlx, game_loop, data);
		state = !state;

	}
	return (0);
}