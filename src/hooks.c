# include "cube.h"

int key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_win(data);
	return (0);
}