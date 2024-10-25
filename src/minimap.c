#include "cube.h"

static t_coords	get_player_coords(t_data *data);
int	 draw_block(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
int	 draw_player(t_data *data);
int	 draw_rays(t_data *data);


void draw_ray_borders(t_data *data)
{
	t_coords player = (t_coords){((double)data->player.x * WINDOW_WIDTH) / (TILE_SIZE * data->cols), ((double)data->player.y * WINDOW_HEIGHT) / (TILE_SIZE * data->lines)};
	t_coords first_ray = (t_coords){player.x + cos(data->player.dir - FOV /2) * WINDOW_WIDTH / 2, player.y + sin(data->player.dir - FOV / 2) * WINDOW_HEIGHT / 2};
	t_coords last_ray = (t_coords){player.x + cos(data->player.dir + FOV /2) * WINDOW_WIDTH / 2, player.y + sin(data->player.dir + FOV / 2) * WINDOW_HEIGHT / 2};

	draw_line(data, player, first_ray, 0x00FF00);
	draw_line(data, player, last_ray, 0x00FF00);


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
			if (data->map[y][x] == '1')
				draw_block(data, x, y, MINIMAP_WALL);
			else
				draw_block(data, x, y, MINIMAP_GRND);
			x++;
		}
		y++;
	}
	draw_player(data);
	draw_ray_borders(data);

	// draw_rays(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}

int draw_block(t_data *data, int x, int y, int color)
{
	int i;
	int j;
	int x_size = (double)MINIMAP_SCALE * WINDOW_WIDTH / data->cols;
	int y_size = (double)MINIMAP_SCALE * WINDOW_HEIGHT / data->lines;

	i = 0;
	while (i < x_size)
	{
		j = 0;
		while (j < y_size)
		{
			my_mlx_pixel_put(&data->mlx, x * x_size + i, y * y_size + j, color);
			j++;
		}
		i++;
	}
	return (0);
}

int	 draw_player(t_data *data)
{
	t_coords	player;

	player =  get_player_coords(data);
	// printf("draw player : player coords: %f %f\n", player.x, player.y);
	my_mlx_pixel_put(&data->mlx, player.x, player.y, 0xFF0000);
	my_mlx_pixel_put(&data->mlx, player.x + 1, player.y, 0xFF0000);
	my_mlx_pixel_put(&data->mlx, player.x, player.y + 1, 0xFF0000);
	my_mlx_pixel_put(&data->mlx, player.x + 1, player.y + 1, 0xFF0000);
	return (0);
}

int	 draw_rays(t_data *data)
{
	(void)data;
	// t_coords	player = get_player_coords(data);
	// printf("draw rays : player coords: %f %f\n", player.x, player.y);
	// int		i;
	// int		x_size = (double)MINIMAP_SCALE * WINDOW_WIDTH / data->cols;
	// int		y_size = (double)MINIMAP_SCALE * WINDOW_HEIGHT / data->lines;

	// i = 0;
	// while (i < WINDOW_WIDTH)
	// {
		// double p_x = (double)data->rays[i].hit.x / (TILE_SIZE * data->cols);
		// double p_y = (double)data->rays[i].hit.y / (TILE_SIZE * data->lines);
		// draw_line(data, player, (t_coords){p_x * x_size, p_y * y_size});
		// printf("data %p : coords: %f %f\n", data, p_x * x_size, p_y * y_size);
		// my_mlx_pixel_put(&data->mlx, p_x * x_size, p_y * y_size, 0x00FFFF);
	// 	++i;
	// }
	return (0);
}

static t_coords	get_player_coords(t_data *data)
{
	t_coords coords;

	double x_size = (double)MINIMAP_SCALE * WINDOW_WIDTH / data->cols;
	double y_size = (double)MINIMAP_SCALE * WINDOW_HEIGHT / data->lines;
	
	double p_x = (double)data->player.x / (TILE_SIZE * data->cols);
	double p_y = (double)data->player.y / (TILE_SIZE * data->lines);
	coords.x = p_x * data->cols* x_size;
	coords.y = p_y * data->cols* y_size;;
	return (coords);
}
