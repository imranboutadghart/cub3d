#include "cube.h"

void	update_rays(t_data *data);

int	game_loop(t_data *data)
{
	// update_rays(data);
	draw_minimap(data);
	update_rays(data);
	data->player.dir += data->player.rot_speed;
	// update_player(data);
	// update_sprites(data);
	// render(data);
	return (0);
}
