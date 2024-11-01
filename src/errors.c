#include "cube.h"

int	error(char *msg)
{
	int bruv = write(2, msg, ft_strlen(msg));
	(void)bruv;
	return (1);
}

int	close_all(t_data *data)
{
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
 	// free other stuff
	(void)data;
	exit(0);
}
