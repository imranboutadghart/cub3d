#include "cube.h"

static int	set_def_hooks(t_data *data);

int	init_data(t_parsing_data data, t_data *out)
{
	out->map = ft_memdup(data.map, data.cols * data.lines * sizeof(char));
	init_player(data, out);
	if (init_mlx(out) || set_def_hooks(out))
		return (free_map(out->map, out->cols), error("Failed to init mlx\n"));
	if (init_textures(data, out))
	{
		destroy_mlx(out);
		return (free_map(out->map, out->cols), error("Failed to init textures\n"));
	}
	mlx_loop(out->mlx.mlx);
	return (0);
}

static int	set_def_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win, 17, 1L << 17, close_all, data);
	mlx_loop_hook(data->mlx.mlx, game_loop, data);
	return (0);
}

void	destroy_data(t_data *data)
{
	destroy_textures(data);
	destroy_mlx(data);
}
