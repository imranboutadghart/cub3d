#include "cube.h"

#define STEP 1
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
		normalize_angle(&angle);
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

	data->rays[i].angle = angle;
	ret_forx = get_x_dist(data, i);
	ret_fory = get_y_dist(data, i);
	if (ret_forx != -1 && (ret_forx < ret_fory || ret_fory == -1))
	{
		dist = ret_forx;
		data->rays[i].hit_direction = 2 + (cos(data->rays[i].angle) >= 0) * 1;
		data->rays[i].texture_offset = data->rays[i].x_texture_offset;
		data->rays[i].hit.x = data->rays[i].tmp_hit_X.x;
		data->rays[i].hit.y = data->rays[i].tmp_hit_X.y;
	}
	else
	{
		dist = ret_fory;
		data->rays[i].hit_direction = (sin(data->rays[i].angle) < 0) * 1;
		data->rays[i].texture_offset = data->rays[i].y_texture_offset;
		data->rays[i].hit.x = data->rays[i].tmp_hit_y.x;
		data->rays[i].hit.y = data->rays[i].tmp_hit_y.y;
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
	double	tan_val;

	angle = data->rays[i].angle;
	if (fabs(cos(angle)) <= EPSILON)
		return (-1);
	ray_direction = cos(angle) >= 0;
	first_step = (TILE_SIZE - ((int)data->player.x % TILE_SIZE)) * (ray_direction)
				- ((int)data->player.x % TILE_SIZE) * (!ray_direction);
	ray_direction = (ray_direction * 1 + !ray_direction * -1);
	tan_val = tan(angle);
	x = data->player.x + first_step;
	y = data->player.y + first_step * tan_val;
	while (!is_out(x, y, data) && !is_wall(x - TILE_SIZE * (ray_direction == -1), y, data))
	{
		x += TILE_SIZE * ray_direction;
		y += TILE_SIZE * tan_val * ray_direction;
	}
	if (is_out(x, y, data))
		return (-1);
	data->rays[i].x_texture_offset = y % TILE_SIZE;
	data->rays[i].tmp_hit_X.x = x;
	data->rays[i].tmp_hit_X.y = y;
	// draw_line(data, (t_coords){((double)data->player.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)data->player.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
	// 			(t_coords){((double)x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
	// 			COLOR5);
	return (sqrt(SQUARE(x - data->player.x) + SQUARE(y - data->player.y)));
}

double get_y_dist(t_data *data, int i)
{
	int		x;
	int		y;
	int		ray_direction;
	int		first_step;
	double	angle;
	double	tan_val;

	angle = data->rays[i].angle;
	if (fabs(sin(angle)) <= EPSILON)
		return (-1);
	ray_direction = sin(angle) >= 0;
	first_step = (TILE_SIZE - ((int)data->player.y % TILE_SIZE)) * (ray_direction)
				- ((int)data->player.y % TILE_SIZE) * (!ray_direction);
	ray_direction = (ray_direction * 1 + !ray_direction * -1);
	tan_val = 1. / tan(angle);
	x = data->player.x + first_step * tan_val;
	y = data->player.y + first_step;
	while (!is_out(x, y, data) && !is_wall(x, y - TILE_SIZE * (ray_direction == -1), data))
	{
		x += (double)TILE_SIZE * tan_val * ray_direction;
		y += TILE_SIZE * ray_direction;
	}
	if (is_out(x, y, data))
		return (-1);
	// draw_line(data, (t_coords){((double)data->player.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)data->player.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
	// 			(t_coords){((double)x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
	// 			COLOR6);
	data->rays[i].y_texture_offset = x % TILE_SIZE;
	data->rays[i].tmp_hit_y.x = x;
	data->rays[i].tmp_hit_y.y = y;
	return (sqrt(SQUARE(x - data->player.x) + SQUARE(y - data->player.y)));
}