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
	}
	else
	{
		dist = ret_fory;
		data->rays[i].hit_direction = (sin(data->rays[i].angle) >= 0) * 1;
	}
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

double get_x_dist(t_data *data, int i)
{

}

int	get_next_tile(int direction, int initial_pos)
{
	if (direction == 0)
		return (initial_pos);
	if (direction > 0)
		return (ceil((double)initial_pos / TILE_SIZE) + 0.1) * TILE_SIZE;
	return (floor((double)initial_pos / TILE_SIZE) + 0.1) * TILE_SIZE;
}