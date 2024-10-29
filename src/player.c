#include "cube.h"

int	init_player(t_parsing_data data, t_data *out)
{
	out->cols = data.cols;
	out->lines = data.lines;
	out->floor_color = data.f;
	out->ceil_color = data.c;
	out->map = data.map;
	out->player.x = (2 + data.player_x) * TILE_SIZE + TILE_SIZE / 2;
	out->player.y = (2 + data.player_y) * TILE_SIZE + TILE_SIZE / 2;
	out->player.dir = PI / 2;
	out->player.rot_speed = ROT_SPEED;
	out->player.walk_speed = 5;
	return (0);
}