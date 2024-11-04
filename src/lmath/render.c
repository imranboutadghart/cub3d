#include "cube.h"

static int	get_height(t_ray ray, double angle);
static void	render_ray(t_data *data, int i);
static int	get_color(t_data *data, t_ray ray, int j);

void	draw_game(t_data *data)
{
	int	i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		render_ray(data, i);
		++i;
	}
}

static void	render_ray(t_data *data, int i)
{
	t_ray	ray;
	int		j;
	int		color;

	ray = data->rays[i];
	j = -1;
	while (++j < WINDOW_HEIGHT)
	{
		color = get_color(data, ray, j);
		my_mlx_pixel_put(&data->mlx, i, j, color);
		continue ;
	}	
}

static int	get_color(t_data *data, t_ray ray, int j)
{
	double		height;
	t_texture	*texture;
	int			x;
	int			y;

	height = get_height(ray, data->player.dir - ray.angle);
	if (j <= WINDOW_HEIGHT / 2 - height / 2)
		return (data->ceil_color);
	if (j >= WINDOW_HEIGHT / 2 + height / 2)
		return (data->floor_color);
	texture = data->textures[ray.hit_direction];
	x = ray.texture_offset;
	j = j - WINDOW_HEIGHT / 2 + height / 2;
	y = j * TILE_SIZE / height;
	return (my_mlx_pixel_get(texture, x, y));
}

static int	get_height(t_ray ray, double angle)
{
	double	height;
	double	view;

	view = ray.dist * tan(FOV / 2) * cos(angle);
	if (!view)
		return (0);
	height = (double)TILE_SIZE * WINDOW_HEIGHT / view;
	return (height);
}