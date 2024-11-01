
# include "cube.h"

int	verify_macros(void)
{
	if (WINDOW_WIDTH < 1 || WINDOW_HEIGHT < 1)
		printf("Invalid window size\n");
	else if (TILE_SIZE < 1)
		printf("Invalid TILE_SIZE\n");
	else if (FOV < 0 || FOV > PI)
		printf("Invalid FOV\n");
	else if (MINIMAP_SCALE <= 0 || MINIMAP_SCALE > 1)
		printf("Invalid MINIMAP_SCALE\n");
	else if (MINIMAP_WALL == MINIMAP_GRND)
		printf("MINIMAP_WALL cannot equal MINIMAP_GRND\n");
	else
		return (0);
	return (1);
}

int main(int ac, char **av)
{
	t_parsing_data	*data;
	t_data			game_data;
	int				ret;

	if (verify_macros())
		return (1);
	data = parse(ac, av);
	ret = init_data(*data, &game_data);
	free_parsing_data(data);
	if (ret)
		return (1);
	// run_game(&data);
	destroy_data(&game_data);
}
