#include "cube.h"

void	rotate_player(t_data *data, int dir);
void	move_player(t_data *data, int x, int y);

void	do_movement(t_data *data)
{
	int	*keys;

	keys = data->pressed_keys;
	if (keys[W_PRESSED] || keys[UP_PRESSED])
		move_player(data, 1, 0);
	if (keys[S_PRESSED] || keys[DOWN_PRESSED])
		move_player(data, -1, 0);
	if (keys[A_PRESSED])
		move_player(data, 0, -1);
	if (keys[D_PRESSED])
		move_player(data, 0, 1);
	if (keys[LEFT_PRESSED])
		rotate_player(data, -1);
	if (keys[RIGHT_PRESSED])
		rotate_player(data, 1);
}

void	move_player(t_data *data, int x, int y)
{
	double	angle;
	int		x_offset;
	int		y_offset;

	// atan2(x, y) returns the angle between the x-axis and the point (x, y) 
	angle = data->player.dir + atan2(y, x);
	x_offset = (int)kill_precision(data->player.walk_speed * cos(angle));
	y_offset = (int)kill_precision(data->player.walk_speed * sin(angle));
	if (is_wall(data->player.x + x_offset, data->player.y + y_offset, data))
	{
		if (!is_wall(data->player.x + x_offset, data->player.y, data))
			y_offset = 0;
		else if (!is_wall(data->player.x, data->player.y + y_offset, data))
			x_offset = 0;
		else
			return ;
	}
	data->player.x += x_offset;
	data->player.y += y_offset;
}

void	rotate_player(t_data *data, int dir)
{
	data->player.dir += dir * data->player.rot_speed * PI / 180;
	normalize_angle(&data->player.dir);
}