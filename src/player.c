#include "cube.h"

int	init_player(t_parsing_data data, t_data *out)
{
	out->cols = data.cols;
	out->lines = data.lines;
	out->floor_color = data.f;
	out->ceil_color = data.c;
	out->player.x = data.player_x * TILE_SIZE + TILE_SIZE / 2;
	out->player.y = data.player_y * TILE_SIZE + TILE_SIZE / 2;
	out->player.dir = INIT_DIR;
	out->player.rot_speed = INIT_ROT_SPEED;
	out->player.walk_speed = INIT_WALK_SPEED;
	return (0);
}