#include "cube.h"

static void	free_textures(t_parsing_data *data);
void	free_map(char **map, int cols);

void	free_parsing_data(t_parsing_data *data)
{
	free_textures(data);
	free_map(data->map, data->cols);
	free(data);
}

void	free_map(char **map, int cols)
{
	for (int i = 0; i < cols; i++)
		free(map[i]);
	free(map);
}

static void	free_textures(t_parsing_data *data)
{
	free(data->e_texture);
	free(data->w_texture);
	free(data->s_texture);
	free(data->n_texture);
}
