#include "cube.h"

static t_coords	get_player_coords(t_data *data);
int	 draw_block(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
int	 draw_player(t_data *data);
int	 draw_rays(t_data *data);

int draw_minimap(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->map[y][x] == '1')
				draw_block(data, x, y, 0xFF0000);
			else
				draw_block(data, x, y, 0x00FF00);
			x++;
		}
		y++;
	}
	draw_player(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}

int draw_block(t_data *data, int x, int y, int color)
{
	int i;
	int j;
	int x_size = (double)MINIMAP_SCALE * WINDOW_WIDTH / data->width;
	int y_size = (double)MINIMAP_SCALE * WINDOW_HEIGHT / data->height;

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
	t_coords	coords;

	coords =  get_player_coords(data);
	my_mlx_pixel_put(&data->mlx, coords.x, coords.y, 0xFF0000);
	my_mlx_pixel_put(&data->mlx, coords.x + 1, coords.y, 0xFF0000);
	my_mlx_pixel_put(&data->mlx, coords.x, coords.y + 1, 0xFF0000);
	my_mlx_pixel_put(&data->mlx, coords.x + 1, coords.y + 1, 0xFF0000);
	return (0);
}

int	 draw_rays(t_data *data)
{
	t_coords	player = get_player_coords(data);
	int		 i;
	int x_size = (double)MINIMAP_SCALE * WINDOW_WIDTH / data->width;
	int y_size = (double)MINIMAP_SCALE * WINDOW_HEIGHT / data->height;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		double p_x = (double)data->rays[i].hit.x / (TILE_SIZE * data->width);
		double p_y = (double)data->rays[i].hit.x / (TILE_SIZE * data->height);
		// draw_line(data, player, (t_coords){data->rays[i].hit.x * x_size, data->rays[i].hit.y * y_size});
		my_mlx_pixel_put(&data->mlx, p_x * x_size, p_y * y_size, 0x00FFFF);
		++i;
	}
	return (0);
}

static t_coords	get_player_coords(t_data *data)
{
	t_coords coords;

	double x_size = (double)MINIMAP_SCALE * WINDOW_WIDTH / data->width;
	double y_size = (double)MINIMAP_SCALE * WINDOW_HEIGHT / data->height;
	printf("data %p : Player coords: %d %d\n",data , data->player.x, data->player.y);
	
	double p_x = (double)data->player.x / (TILE_SIZE * data->width);
	double p_y = (double)data->player.y / (TILE_SIZE * data->height);
	coords.x = p_x * data->width * x_size;
	coords.y = p_y * data->width * y_size;;
	return (coords);
}
