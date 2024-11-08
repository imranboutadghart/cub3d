#include "cube.h"

// static t_coords	get_player_coords(t_data *data);
static t_coords	scale_to_minimap(t_data *data, t_coords coords);
static void		draw_ray_borders(t_data *data);
static int		draw_block(t_data *data, int x, int y, double size, int color);
static int		draw_player(t_data *data);
static int		draw_rays(t_data *data);

# define calc(x1, y1, x2, y2) sqrt(SQUARE((x2) - (x1)) + SQUARE((y2) - (y1)))

// the function that draws minimap
int draw_minimap(t_data *data)
{
	int x;
	int y;

	if (MINIMAP_SCALE < EPSILON)
		return (1);
	y = 0;
	// these whiles to print the background of the map
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
	// draws the player as a square
	draw_player(data);
	// loops over each ray and draws it
	draw_rays(data);
	// this one is prolly wrong
	draw_ray_borders(data);
	return (0);
}

int draw_block(t_data *data, int x, int y, double size, int color)
{
	int i;
	int j;
	double	y_size;
	// everything is scaled down
	t_coords	coords = scale_to_minimap(data, (t_coords){x, y});
	size = size * MINIMAP_SCALE * WINDOW_WIDTH / data->cols;
	y_size = size * WINDOW_HEIGHT / WINDOW_WIDTH;

	i = 0;
	// draws a block with nigga borders
	while (i < size)
	{
		j = 0;
		while (j < y_size)
		{
			if (!i || !j || i == size - 1 || j == y_size - 1)
				my_mlx_pixel_put(&data->mlx, coords.x + i, coords.y + j, 0x000);
			else
				my_mlx_pixel_put(&data->mlx, coords.x + i, coords.y + j, color);
			j++;
		}
		i++;
	}
	return (0);
}

int	 draw_player(t_data *data)
{
	// draws a block at (x, y) of player block size is .1 normal size
	draw_block(data, data->player.x, data->player.y, 0.1, COLOR3);
	return (0);
}

int	 draw_rays(t_data *data)
{
	(void)data;
	int		i;

	i = 0;
	// loops over rays and draws line from player(x, y) to ray.hit(x, y)
	//!! you should probably redo draw_line cuz ghi zrbt 3liha
	while (i < WINDOW_WIDTH)
	{
		draw_line(data, scale_to_minimap(data, (t_coords){data->player.x, data->player.y}),
					scale_to_minimap(data, (t_coords){data->rays[i].hit.x, data->rays[i].hit.y}),
					(data->rays[i].hit_direction & 2) ? COLOR8 : COLOR6);
		++i;
	}
	return (0);
}

static t_coords	scale_to_minimap(t_data *data, t_coords coords)
{
	// this where you could move you stuff around
	t_coords res;

	res.x = coords.x * MINIMAP_SCALE * WINDOW_WIDTH / 
			(TILE_SIZE * data->cols);
	res.y = coords.y * MINIMAP_SCALE * WINDOW_HEIGHT / 
			(TILE_SIZE * data->lines);
	return (res);
}

void draw_ray_borders(t_data *data)
{
	(void)data;
	t_coords p = scale_to_minimap(data, (t_coords){data->player.x, data->player.y});
	t_coords f = (t_coords){p.x + cos(data->player.dir - FOV /2) * MINIMAP_SCALE * TILE_SIZE / 2, p.y + sin(data->player.dir - FOV / 2) * MINIMAP_SCALE * TILE_SIZE / 2};
	t_coords l = (t_coords){p.x + cos(data->player.dir + FOV /2) * MINIMAP_SCALE * TILE_SIZE / 2, p.y + sin(data->player.dir + FOV / 2) * MINIMAP_SCALE * TILE_SIZE / 2};

	draw_line(data, p, f, 0xFF0000);
	draw_line(data, p, l, 0xFF0000);
}
