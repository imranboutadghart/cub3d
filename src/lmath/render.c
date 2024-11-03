#include "cube.h"

static int	should_draw(t_ray ray, int i, double angle);
static void	render_ray(t_data *data, int i);

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
	int		is_sky;
	static int colors[4] = {COLOR9, COLOR10, COLOR11, COLOR12};
	int		color;

	ray = data->rays[i];
	j = -1;
	is_sky = 1;
	while (++j < WINDOW_HEIGHT)
	{
		if (should_draw(ray, j, data->player.dir))
		{
			color = colors[ray.hit_direction];
			my_mlx_pixel_put(&data->mlx, i, j, color);
			is_sky = 0;
			continue ;
		}
		if (is_sky)
			my_mlx_pixel_put(&data->mlx, i, j, data->ceil_color);
		else
			my_mlx_pixel_put(&data->mlx, i, j, data->floor_color);
	}	
}

static int	should_draw(t_ray ray, int i, double angle)
{
	int	height;

	height = sin(10. / ray.dist) * WINDOW_HEIGHT;
	// height = WINDOW_HEIGHT - (ray.dist * cos(fabs(ray.angle - angle))) / 2;
	// height = height * (height > 6) + 6 * (height <= 0);
	return (i > WINDOW_HEIGHT / 2 - height / 2 && i < WINDOW_HEIGHT / 2 + height / 2);
}