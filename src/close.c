#include "cube.h"

int	close_win(t_data *data)
{
// 	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
// 	mlx_destroy_display(data->mlx.mlx);
// 	free(data->mlx.mlx);
// 	// free other stuff
	(void)data;
	exit(0);
}

void	destroy_data(t_data *data)
{
	destroy_textures(data);
	destroy_mlx(data);
}