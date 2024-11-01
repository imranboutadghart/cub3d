#include "cube.h"

void	update_rays(t_data *data);


int	game_loop(t_data *data)
{
	limit_fps(FPS);
	do_movement(data);
	update_rays(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	// render(data);
	return (0);
}

int	game_pause(t_data *data)
{
	(void)data;
	return (0);
}