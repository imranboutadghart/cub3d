#include "cube.h"

int	init_player(t_parsing_data data, t_data *out)
{
	out->map = data.map;
	out->player.x = data.player_x * TILE_SIZE + TILE_SIZE / 2;
	out->player.y = data.player_y * TILE_SIZE + TILE_SIZE / 2;
	out->player.dir = 0;
	out->player.rot_speed = PI / 180;
	out->player.walk_speed = 5;
	return (0);
}