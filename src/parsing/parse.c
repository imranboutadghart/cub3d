#include "cube.h"

# define MAP_WIDTH 20
# define MAP_HEIGHT 20
static char	**get_map(void);

t_parsing_data	*parse(int ac, char **av)
{
	t_parsing_data	*data;

	(void) ac;
	(void) av;
	data = malloc(sizeof(t_parsing_data));
	data->e_texture = ft_strdup(TEXTURE_E);
	data->w_texture = ft_strdup(TEXTURE_W);
	data->s_texture = ft_strdup(TEXTURE_S);
	data->n_texture = ft_strdup(TEXTURE_N);
	data->f = 0x964B00;
	data->c = 0x87CEEB;
	// map to not be freed
	data->map = get_map();
	data->cols = MAP_WIDTH;
	data->lines = MAP_HEIGHT;
	data->player_x = MAP_WIDTH / 2;
	data->player_y = MAP_HEIGHT / 2;
	return (data);
}

// don't free map, mafiach li iduppiha
static char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * MAP_WIDTH);
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		map[i] = malloc(sizeof(char) * MAP_HEIGHT);
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (i == 0 || i == MAP_WIDTH - 1 || j == 0 || j == MAP_HEIGHT - 1)
				map[i][j] = '1';
			else
				map[i][j] = '0';
		}
	}
	map[3][7] = '1';
	map[5][7] = '1';
	map[3][4] = '1';
	map[MAP_WIDTH / 2][MAP_HEIGHT / 2] = 'P';
	return (map);
}
