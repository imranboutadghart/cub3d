#include "cube.h"

int init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (1);
	data->mlx.win = mlx_new_window(&data->mlx, data->width, data->height, "cub3d");
	if (!data->mlx.win)
	{
		mlx_destroy_display(data->mlx.mlx);
		return (1);
	}
	return (0);
}

void	destroy_mlx(t_data *data)
{
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx);
}