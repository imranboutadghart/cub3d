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
	if (angle >= PI * 2)
		angle -= PI * 2;
	if (angle < PI * 2)
		angle += PI * 2;
	while (i < WINDOW_WIDTH)
	{
		// printf("angle: %f\n", angle * 180 / PI);
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
		data->rays[i].hit.x = data->rays[i].hit_x.x;
		data->rays[i].hit.y = data->rays[i].hit_x.y;
	}
	else
	{
		dist = ret_fory;
		data->rays[i].hit_direction = (sin(data->rays[i].angle) < 0) * 1;
		data->rays[i].texture_offset = data->rays[i].y_texture_offset;
		data->rays[i].hit.x = data->rays[i].hit_y.x;
		data->rays[i].hit.y = data->rays[i].hit_y.y;
	}
	data->rays[i].dist = dist;
	// printf("i: %d, xdist: %f, ydist: %f\n", i, ret_forx, ret_fory);
	// my_mlx_pixel_put(&data->mlx, ((double)data->rays[i].hit.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols)    , ((double)data->rays[i].hit.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)    , 0x0000aa);
	// draw_line(data, (t_coords){((double)data->player.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)data->player.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
	// 				(t_coords){((double)data->rays[i].hit.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)data->rays[i].hit.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
	// 				data->rays[i].hit_direction & 2 ? 0x00FF00 : 0xFF0000);
	// my_mlx_pixel_put(&data->mlx, ((double)data->rays[i].hit.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols) + 1, ((double)data->rays[i].hit.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)    , 0x0000aa);
	// my_mlx_pixel_put(&data->mlx, ((double)data->rays[i].hit.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols)    , ((double)data->rays[i].hit.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines) + 1, 0x0000aa);
	// my_mlx_pixel_put(&data->mlx, ((double)data->rays[i].hit.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols) + 1, ((double)data->rays[i].hit.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines) + 1, 0x0000aa);
	return (dist);
}

double get_x_dist(t_data *data, int i)
{
	int		x;
	int		y;
	int		ray_direction;
	int		first_step;
	int		direction;
	double	angle;

	angle = data->rays[i].angle;
	if (fabs(cos(angle)) <= EPSILON)
	{
		// printf("x-angle too small\n");
		return (-1);
	}
	ray_direction = cos(angle) >= 0;
	first_step = (TILE_SIZE - ((int)data->player.x % TILE_SIZE)) * (ray_direction)
				- ((int)data->player.x % TILE_SIZE) * (!ray_direction);
	direction = (ray_direction * 1 + !ray_direction * -1);
	x = data->player.x + first_step * direction;
	y = data->player.y + first_step * (tan(angle) * direction);
	while (!is_out(x, y, data) &&
			data->map[x / TILE_SIZE][y / TILE_SIZE] != '1')
	{
		x += TILE_SIZE * direction /** (ray_direction * 1 + !ray_direction * -1)*/;
		y += TILE_SIZE * (tan(angle) * direction);
	}
	if (is_out(x, y, data))
	{
		// printf("angle: %f, x-out\n", angle * 180);
		return (-1);
	}
	data->rays[i].x_texture_offset = y % TILE_SIZE;
	data->rays[i].hit_x.x = x + TILE_SIZE * !ray_direction;
	data->rays[i].hit_x.y = y;
	printf("x: %d, y: %d,   angle: %f, myval: %f\n", x, y, angle * 180 / PI, tan(angle));
	draw_line(data, (t_coords){((double)data->player.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)data->player.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
				(t_coords){((double)x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
				0x00FFFF);
	return (sqrt(SQUARE(x - data->player.x) + SQUARE(y - data->player.y)));
}

double get_y_dist(t_data *data, int i)
{
	int		x;
	int		y;
	int		ray_direction;
	int		first_step;
	double	angle;

	angle = data->rays[i].angle;
	if (fabs(sin(angle)) <= EPSILON)
	{
		// printf("y-angle too small\n");
		return (-1);
	}
	ray_direction = sin(angle) >= 0;
	first_step = (TILE_SIZE - ((int)data->player.x % TILE_SIZE)) * (ray_direction)
				- ((int)data->player.x % TILE_SIZE) * (!ray_direction);
	x = data->player.x + first_step * atan(angle);
	y = data->player.y + first_step;
	while (!is_out(x, y, data) &&
			data->map[x / TILE_SIZE][y / TILE_SIZE] != '1')
	{
		x += (double)TILE_SIZE / tan(angle);
		y += TILE_SIZE * (ray_direction * 1 + !ray_direction * -1);
	}
	if (is_out(x, y, data))
	{
		// printf("angle: %f, y-out\n", angle * 180);
		return (-1);
	}
	// draw_line(data, (t_coords){((double)data->player.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)data->player.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
	// 			(t_coords){((double)x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
	// 			0xFF00FF);
	data->rays[i].y_texture_offset = x % TILE_SIZE;
	data->rays[i].hit_y.x = x;
	data->rays[i].hit_y.y = y;
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
