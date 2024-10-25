#include "cube.h"

# define MAP_WIDTH 20
# define MAP_HEIGHT 20

char	**get_map(void)
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
	map[MAP_WIDTH / 2][MAP_HEIGHT / 2] = 'P';
	return (map);
}

void	free_map(char **map)
{
	for (int i = 0; i < MAP_WIDTH; i++)
		free(map[i]);
	free(map);
}

t_parsing_data	*parse(int ac, char **av)
{
	t_parsing_data	*data;

	(void) ac;
	(void) av;
	data = malloc(sizeof(t_parsing_data));
	data->e_texture = TEXTURE_E;
	data->w_texture = TEXTURE_W;
	data->s_texture = TEXTURE_S;
	data->n_texture = TEXTURE_N;
	data->f = 0;
	data->c = 0x000020c4;
	data->map = get_map();
	data->cols = MAP_WIDTH;
	data->lines = MAP_HEIGHT;
	data->player_x = MAP_WIDTH / 2;
	data->player_y = MAP_HEIGHT / 2;
	return (data);
}

