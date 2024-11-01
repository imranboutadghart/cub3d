#include "cube.h"

// static t_coords	get_player_coords(t_data *data);
static t_coords	scale_to_minimap(t_data *data, t_coords coords);
int	 draw_block(t_data *data, int x, int y, double size, int color);
void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
int	 draw_player(t_data *data);
int	 draw_rays(t_data *data);

# define calc(x1, y1, x2, y2) sqrt(SQUARE((x2) - (x1)) + SQUARE((y2) - (y1)))

void draw_ray_borders(t_data *data)
{
	(void)data;
	t_coords p = scale_to_minimap(data, (t_coords){data->player.x, data->player.y});
	t_coords f = (t_coords){p.x + kill_precision(cos(data->player.dir - FOV /2)) * TILE_SIZE / 2, p.y + kill_precision(sin(data->player.dir - FOV / 2)) * TILE_SIZE / 2};
	t_coords l = (t_coords){p.x + kill_precision(cos(data->player.dir + FOV /2)) * TILE_SIZE / 2, p.y + kill_precision(sin(data->player.dir + FOV / 2)) * TILE_SIZE / 2};

	// printf("angle between borders: %f\n", acos((SQUARE(calc(p.x, p.y, f.x, f.y)) + SQUARE(calc(p.x, p.y, l.x, l.y)) - calc(f.x, f.y, l.x, l.y)) / (2 * calc(p.x, p.y, f.x, f.y) * calc(p.x, p.y, l.x, l.y))));
	draw_line(data, p, f, 0xFF0000);
	draw_line(data, p, l, 0xFF0000);
}

int draw_minimap(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->lines)
	{
		x = 0;
		while (x < data->cols)
		{
			if (data->map[x][y] == '1')
				draw_block(data, x * TILE_SIZE, y * TILE_SIZE, 1, MINIMAP_WALL);
			else
				draw_block(data, x * TILE_SIZE, y * TILE_SIZE, 1, MINIMAP_GRND);
			x++;
		}
		y++;
	}
	draw_player(data);
	draw_ray_borders(data);

	draw_rays(data);
	return (0);
}

int draw_block(t_data *data, int x, int y, double size, int color)
{
	int i;
	int j;
	// int x_size = size * MINIMAP_SCALE * WINDOW_WIDTH / data->cols;
	// int y_size = size * MINIMAP_SCALE * WINDOW_HEIGHT / data->lines;
	t_coords	coords = scale_to_minimap(data, (t_coords){x, y});
	size = size * MINIMAP_SCALE * WINDOW_WIDTH / data->cols;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(&data->mlx, coords.x + i, coords.y + j, color);
			j++;
		}
		i++;
	}
	return (0);
}

int	 draw_player(t_data *data)
{
	// printf("player coords before scaling: %d %d\n", data->player.x, data->player.y);
	// printf("player coords after scaling: %d %d\n", player.x, player.y);
	draw_block(data, data->player.x, data->player.y, 0.1, COLOR3);
	return (0);
}

int	 draw_rays(t_data *data)
{
	(void)data;
	// t_coords	player = get_player_coords(data);
	// printf("draw rays : player coords: %f %f\n", player.x, player.y);
	int		i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		// draw_line(data, (t_coords){((double)data->player.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)data->player.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
		// 			(t_coords){((double)data->rays[i].hit.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)data->rays[i].hit.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)},
		// 			COLOR8);
		draw_line(data, scale_to_minimap(data, (t_coords){data->player.x, data->player.y}),
					scale_to_minimap(data, (t_coords){data->rays[i].hit.x, data->rays[i].hit.y}),
					COLOR8);
		// printf("data %p : coords: %f %f\n", data, p_x * x_size, p_y * y_size);
		// my_mlx_pixel_put(&data->mlx, p_x * x_size, p_y * y_size, 0x00FFFF);
		++i;
	}
	return (0);
}

// static t_coords	get_player_coords(t_data *data)
// {
// 	t_coords coords;

// 	double x_size = (double)MINIMAP_SCALE * WINDOW_WIDTH / data->cols;
// 	double y_size = (double)MINIMAP_SCALE * WINDOW_HEIGHT / data->lines;
	
// 	double p_x = (double)data->player.x / (TILE_SIZE * data->cols);
// 	double p_y = (double)data->player.y / (TILE_SIZE * data->lines);
// 	coords.x = p_x * data->cols* x_size;
// 	coords.y = p_y * data->cols* y_size;;
// 	return (coords);
// }

static t_coords	scale_to_minimap(t_data *data, t_coords coords)
{
	t_coords res;

	res.x = coords.x * MINIMAP_SCALE * WINDOW_WIDTH / (TILE_SIZE * data->cols);
	res.y = coords.y * MINIMAP_SCALE * WINDOW_HEIGHT / (TILE_SIZE * data->lines);
	return (res);
}
