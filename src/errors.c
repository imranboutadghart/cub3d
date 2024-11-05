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

int	verify_macros(void)
{
	if (WINDOW_WIDTH < 1 || WINDOW_HEIGHT < 1)
		printf("Invalid window size\n");
	else if (TILE_SIZE < 1)
		printf("Invalid TILE_SIZE\n");
	else if (FOV < 0 || FOV > PI)
		printf("Invalid FOV\n");
	else if (MINIMAP_SCALE < 0 || MINIMAP_SCALE > 1)
		printf("Invalid MINIMAP_SCALE\n");
	else if (MINIMAP_WALL == MINIMAP_GRND)
		printf("MINIMAP_WALL cannot equal MINIMAP_GRND\n");
	else
		return (0);
	return (1);
}
