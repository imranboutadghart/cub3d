
# include "cube.h"

int main(int ac, char **av)
{
	t_parsing_data	*data;
	t_data			game_data;
	int				ret;

	data = parse(ac, av);
	ret = init_data(*data, &game_data);
	free_parsing_data(data);
	if (ret)
		return (1);
	// run_game(&data);
	destroy_data(&game_data);
}
