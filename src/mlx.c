#include "cube.h"

int init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (1);
	data->mlx.win = mlx_new_window(data->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, NAME);
	if (!data->mlx.win)
	{
		mlx_destroy_display(data->mlx.mlx);
		return (1);
	}
	data->mlx.img = mlx_new_image(data->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp, &data->mlx.ll, &data->mlx.endian);
	return (0);
}

void	destroy_mlx(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx);
}
