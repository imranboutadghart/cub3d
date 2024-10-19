#include "cube.h"

#define STEP 1
int get_next_tile(int direction, int initial_pos);
static double	cast_ray(t_data *data, int i, double angle);
double get_x_dist(t_data *data, int i);
double get_y_dist(t_data *data, int i);

void	update_rays(t_data *data)
{
	int	i;
	double	angle;

	i = 0;
	angle = data->player.dir - FOV / 2;
	while (i < WINDOW_WIDTH)
	{
		cast_ray(data, i, angle);
		angle += (double)FOV / WINDOW_WIDTH;
		i++;
	}
}

static double	cast_ray(t_data *data, int i, double angle)
{
	double  ret_forx;
	double  ret_fory;
	double	dist;
	int		x;
	int		y;
	int		direction_x;
	int		direction_y;

	data->rays[i].angle = angle;
	ret_forx = get_x_dist(data, i);
	ret_fory = get_y_dist(data, i);
	if (ret_forx < ret_fory || ret_fory == -1)
	{
		dist = ret_forx;
		data->rays[i].hit_direction = 2 + (cos(data->rays[i].angle) >= 0) * 1;
		data->rays[i].texture_offset = data->rays[i].x_texture_offset;
	}
	else
	{
		dist = ret_fory;
		data->rays[i].hit_direction = (sin(data->rays[i].angle) < 0) * 1;
		data->rays[i].texture_offset = data->rays[i].y_texture_offset;
	}
	data->rays[i].dist = dist;
	return (dist);
}

double get_x_dist(t_data *data, int i)
{
	int		x;
	int		y;
	int		ray_direction;
	int		first_step;
	double	angle;

	angle = data->rays[i].angle;
	if (cos(angle) <= EPSILON)
		return (-1);
	ray_direction = cos(angle) >= 0;
	first_step = (TILE_SIZE - ((int)data->player.x % TILE_SIZE)) * (ray_direction)
				- ((int)data->player.x % TILE_SIZE) * (!ray_direction);
	x = data->player.x + first_step;
	y = data->player.y + first_step * (tan(angle));
	while (!is_out(x, y, data) &&
			data->map[x / TILE_SIZE][y / TILE_SIZE] != '1')
	{
		x += TILE_SIZE;
		y += TILE_SIZE * tan(angle);
	}
	if (is_out(x, y, data))
		return (-1);
	data->rays[i].x_texture_offset = y % TILE_SIZE;
	return (SQUARE(x - data->player.x) + SQUARE(y - data->player.y));
}


double get_y_dist(t_data *data, int i)
{
	int		x;
	int		y;
	int		ray_direction;
	int		first_step;
	double	angle;

	angle = data->rays[i].angle;
	if (sin(angle) <= EPSILON)
		return (-1);
	ray_direction = sin(angle) >= 0;
	first_step = (TILE_SIZE - ((int)data->player.x % TILE_SIZE)) * (ray_direction)
				- ((int)data->player.x % TILE_SIZE) * (!ray_direction);
	x = data->player.x + first_step * atan(angle);
	y = data->player.y + first_step;
	while (!is_out(x, y, data) &&
			data->map[x / TILE_SIZE][y / TILE_SIZE] == '1')
	{
		x += (double)TILE_SIZE / tan(angle);
		y += TILE_SIZE;
	}
	if (is_out(x, y, data))
		return (-1);
	data->rays[i].y_texture_offset = x % TILE_SIZE;
	return (sqrt(SQUARE(x - data->player.x) + SQUARE(y - data->player.y)));
}

int	get_next_tile(int direction, int initial_pos)
{
	if (direction == 0)
		return (initial_pos);
	if (direction > 0)
		return (ceil((double)initial_pos / TILE_SIZE) + 0.1) * TILE_SIZE;
	return (floor((double)initial_pos / TILE_SIZE) + 0.1) * TILE_SIZE;
}