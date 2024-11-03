#include "cube.h"

#define STEP 1
static double	cast_ray(t_data *data, int i, double angle);
double	get_x_dist(t_data *data, int i, double angle);
double	get_y_dist(t_data *data, int i, double angle);
int		next_tile(int val, int ray_direction);

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

	data->rays[i].angle = angle;
	ret_forx = get_x_dist(data, i, angle);
	ret_fory = get_y_dist(data, i, angle);
	if (ret_forx != -1 && (ret_forx < ret_fory || ret_fory == -1))
	{
		data->rays[i].dist = ret_forx;
		data->rays[i].hit_direction = 2 + (cos(data->rays[i].angle) >= 0) * 1;
		data->rays[i].texture_offset = data->rays[i].x_texture_offset;
		data->rays[i].hit = data->rays[i].tmp_hit_x;
	}
	else
	{
		data->rays[i].dist = ret_fory;
		data->rays[i].hit_direction = (sin(data->rays[i].angle) < 0) * 1;
		data->rays[i].texture_offset = data->rays[i].y_texture_offset;
		data->rays[i].hit = data->rays[i].tmp_hit_y;
	}
	return (data->rays[i].dist);
}

double get_x_dist(t_data *data, int i, double angle)
{
	t_coords	pnt;
	int		ray_direction;
	double	tan_val;

	if (fabs(cos(angle)) <= EPSILON)
		return (-1);
	ray_direction = cos(angle) >= 0;
	tan_val = tan(angle);
	pnt.x = data->player.x + next_tile(data->player.x, ray_direction);
	pnt.y = data->player.y + next_tile(data->player.x, ray_direction) * tan_val;
	ray_direction = (ray_direction * 1 + !ray_direction * -1);
	while (!is_wall(pnt.x - TILE_SIZE * (ray_direction == -1), pnt.y, data))
	{
		pnt.x += TILE_SIZE * ray_direction;
		pnt.y += TILE_SIZE * tan_val * ray_direction;
	}
	if (is_out(pnt.x, pnt.y, data))
		return (-1);
	data->rays[i].x_texture_offset = pnt.y % TILE_SIZE;
	data->rays[i].tmp_hit_x = (t_coords){pnt.x, pnt.y};
	return (sqrt(square(pnt.x - data->player.x) + square(pnt.y - data->player.y)));
}

double get_y_dist(t_data *data, int i, double angle)
{
	t_coords	pnt;
	int		ray_direction;
	double	tan_val;

	if (fabs(sin(angle)) <= EPSILON)
		return (-1);
	ray_direction = sin(angle) >= 0;
	tan_val = 1. / tan(angle);
	pnt.x = data->player.x + next_tile(data->player.x, ray_direction) * tan_val;
	pnt.y = data->player.y + next_tile(data->player.x, ray_direction);
	ray_direction = (ray_direction * 1 + !ray_direction * -1);
	while (!is_wall(pnt.x, pnt.y - TILE_SIZE * (ray_direction == -1), data))
	{
		pnt.x += (double)TILE_SIZE * tan_val * ray_direction;
		pnt.y += TILE_SIZE * ray_direction;
	}
	if (is_out(pnt.x, pnt.y, data))
		return (-1);
	data->rays[i].y_texture_offset = pnt.x % TILE_SIZE;
	data->rays[i].tmp_hit_y = (t_coords){pnt.x, pnt.y};
	return (sqrt(SQUARE(pnt.x - data->player.x) + SQUARE(pnt.y - data->player.y)));
}

int	next_tile(int val, int ray_direction)
{
	if (ray_direction)
		return ((TILE_SIZE - (val % TILE_SIZE)));
	else
		return (-(val % TILE_SIZE));
}
