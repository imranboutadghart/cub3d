
# include "cube.h"

int main(int ac, char **av)
{
	t_parsing_data	*data;
	t_data			game_data;

	data = parse(ac, av);
	if (init_data(*data, &game_data))
	{
		free_map(data->map);
		free(data);
		return (1);
	}
	free_map(data->map);
	free(data);
	// game_loop(&data);
	destroy_data(&game_data);
}
