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
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}

void my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}
