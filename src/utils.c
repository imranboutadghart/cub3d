#include "cube.h"

int	is_out(int x, int y, t_data *data)
{
	(void) data;
	if (x < 0 || y < 0)
		return (1);
	if (x > data->width * TILE_SIZE)
		return (1);
	if (y > data->height * TILE_SIZE)
		return (1);
	if (data->map[x / TILE_SIZE][y / TILE_SIZE] == -1)
		return (1);
	return (0);
}