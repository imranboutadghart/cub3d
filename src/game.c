#include "cube.h"

void	update_rays(t_data *data);

int	game_loop(t_data *data)
{
	// update_rays(data);
	draw_minimap(data);
	update_rays(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	data->player.dir = data->player.dir + data->player.rot_speed * PI / (180 * 5);
	normalize_angle(&data->player.dir);
	// update_player(data);
	// update_sprites(data);
	// render(data);
	return (0);
}

int	game_pause(t_data *data)
{
	(void)data;
	return (0);
}