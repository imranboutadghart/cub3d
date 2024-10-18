#include "cube.h"

#define STEP 1
int get_next_tile(int direction, int initial_pos);

void	update_rays(t_data *data)
{
	int	i;
	double	angle;

	i = 0;
	angle = data->player.dir - FOV / 2;
	while (i < WINDOW_WIDTH)
	{
		data->rays[i].angle = angle;
		data->rays[i].dist = cast_ray(data, angle);
		angle += FOV / WINDOW_WIDTH;
		i++;
	}
}

static double	cast_ray(t_data *data, int i)
{
	double	dist;
	int		x;
	int		y;
	int		direction_x;
	int		direction_y;

	direction_x = (cos(data->rays[i].angle) > 0) + (cos(data->rays[i].angle) < 0) * -1;
	direction_y = (sin(data->rays[i].angle) > 0) + (sin(data->rays[i].angle) < 0) * -1;

	x = get_next_tile(direction_x, data->player.x);
	y = get_next_tile(direction_y, data->player.y);
	dist = 0;
	while (!is_out(x, y, data) && data->map[x / TILE_SIZE][y / TILE_SIZE] != '1')
	{
		x += direction_x * STEP;
		y += direction_y * STEP;
		dist += STEP;
		if (data->map[x / TILE_SIZE][y / TILE_SIZE] == '1')
			break ;
	}
	data->rays[i].hit = 0;
	if ((!is_out(x, y, data) \
	&& data->map[x / TILE_SIZE][y / TILE_SIZE] == '1'))
	{
		data->rays[i].hit = 1;
		data->rays[i].hit_direction = (cos(data->rays[i].angle) >= 0) * 1 + (sin(data->rays[i].angle) >= 0) * 2;
	}
	return (dist);
}

int	get_next_tile(int direction, int initial_pos)
{
	if (direction == 0)
		return (initial_pos);
	if (direction > 0)
		return (ceil((double)initial_pos / TILE_SIZE) + 0.1) * TILE_SIZE;
	return (floor((double)initial_pos / TILE_SIZE) + 0.1) * TILE_SIZE;
}