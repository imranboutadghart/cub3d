
# include "cube.h"

int main(int ac, char **av)
{
	t_parsing_data	*data;
	t_data			game_data;
	int				ret;

	// verify if the macros are not gonna screw things up
	if (verify_macros())
		return (1);
	// return parsed data
	data = parse(ac, av);
	// the one that does the things
	ret = init_data(*data, &game_data);
	// freeing parsing data
	free_parsing_data(data);
	if (ret)
		return (1);
	// destroying game data
	destroy_data(&game_data);
}
