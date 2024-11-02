#include "cube.h"

int	is_out(int x, int y, t_data *data)
{
	(void) data;
	if (x < 0 || y < 0)
		return (1);
	if (x >= data->cols * TILE_SIZE)
		return (1);
	if (y >= data->lines * TILE_SIZE)
		return (1);
	if (data->map[x / TILE_SIZE][y / TILE_SIZE] == -1)
		return (1);
	return (0);
}

int	is_wall(int x, int y, t_data *data)
{
	if (is_out(x, y, data))// don't know whether i should consider -1 a wall or not
		return (1);
	if (data->map[x / TILE_SIZE][y / TILE_SIZE] == '1')
		return (1);
	return (0);
}