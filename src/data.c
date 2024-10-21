#include "cube.h"

void	parse_to_data(t_parsing_data parse, t_data *data);

static int	set_def_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	// mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx.win, 17, 1L << 17, close_win, data);
	// mlx_loop_hook(data->mlx.mlx, game_loop, data);
	game_loop(data);
	return (0);
}

int	init_data(t_parsing_data data, t_data *out)
{
	parse_to_data(data, out);
	if (init_mlx(out) || set_def_hooks(out))
		return (error("Failed to init mlx\n"));
	if (init_textures(data, out))
	{
		destroy_mlx(out);
		return (error("Failed to init textures\n"));
	}
	init_player(data, out);
	// init sprites
	// init raycasting
	// init game loop
	mlx_loop(out->mlx.mlx);
	return (0);
}

void	destroy_data(t_data *data)
{
	destroy_textures(data);
	destroy_mlx(data);
}

void	parse_to_data(t_parsing_data parse, t_data *data)
{
	data->width = parse.width;
	data->height = parse.height;
	data->floor_color = parse.f;
	data->ceil_color = parse.c;
	data->map = parse.map;
	data->player.x = parse.player_x * TILE_SIZE + TILE_SIZE / 2;
	data->player.y = parse.player_y * TILE_SIZE + TILE_SIZE / 2;
}