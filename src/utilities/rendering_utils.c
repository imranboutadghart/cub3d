#include "cube.h"

int	equal(t_coords a, t_coords b)
{
	return (abs(a.x - b.x) < 3 && abs(a.y - b.y) < 3);
}

int draw_line(t_data *data, t_coords start, t_coords end, int color)
{
	int dx = abs(start.x - end.x);
	int dy = abs(start.y - end.y);
	double  ratio = (dx < dy) ? (double)dx / dy : (double)dy / dx;
	double sx = start.x > end.x ? -1 : 1;
	double sy = start.y > end.y ? -1 : 1;
	sx *= (dx < dy)? ratio : 1;
	sy *= (dx < dy)? 1 : ratio;

	double wx = start.x;
	double wy = start.y;
	while (!equal((t_coords){wx, wy}, end))
	{
		my_mlx_pixel_put(&data->mlx, wx, wy, color);
		wx += sx;
		wy += sy;
	}
	return (0);
}

void my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_pixel_get(t_texture *data, int x, int y)
{
	char *dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	normalize_angle(double *angle)
{
	if (*angle >= PI * 2)
		*angle -= PI * 2;
	if (*angle < 0)
		*angle += PI * 2;
}

float	kill_precision(float x)
{
	return (round(x * 1000000) / 1000000);
}

long	get_time()
{
	time_t		now;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	now = tv.tv_usec + (tv.tv_sec % 1000000) * 1000000;
	return (now);
}

void	limit_fps(int fps)
{
	static int	last_time;
	int			current_time;

	if (fps <= 0)
		return ;
	if (!last_time)
		last_time = get_time();
	current_time = get_time();
	while (current_time - last_time < 1000000. / fps)
	{
		usleep(100);
		current_time = get_time();
	}
	last_time = current_time;
}
