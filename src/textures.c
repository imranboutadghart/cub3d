#include "cube.h"

static t_texture	*load_texture(char *path, void *mlx);
static void	unload_texture(t_texture *texture, void *mlx);

int init_textures(t_parsing_data data, t_data *out)
{
	out->textures.texture_e = load_texture(data.e_texture, out->mlx.mlx);
	if (!out->textures.texture_e)
		return (1);
	out->textures.texture_w = load_texture(data.w_texture, out->mlx.mlx);
	if (!out->textures.texture_w)
	{
		unload_texture(out->textures.texture_e, out->mlx.mlx);
		return (1);
	}
	out->textures.texture_s = load_texture(data.s_texture, out->mlx.mlx);
	if (!out->textures.texture_w)
	{
		unload_texture(out->textures.texture_e, out->mlx.mlx);
		unload_texture(out->textures.texture_w, out->mlx.mlx);
		return (1);
	}
	out->textures.texture_n = load_texture(data.n_texture, out->mlx.mlx);
	if (!out->textures.texture_w)
	{
		unload_texture(out->textures.texture_e, out->mlx.mlx);
		unload_texture(out->textures.texture_w, out->mlx.mlx);
		unload_texture(out->textures.texture_s, out->mlx.mlx);
		return (1);
	}
	return (0);
}

void destroy_textures(t_data *data)
{
	unload_texture(data->textures.texture_e, data->mlx.mlx);
	unload_texture(data->textures.texture_w, data->mlx.mlx);
	unload_texture(data->textures.texture_s, data->mlx.mlx);
	unload_texture(data->textures.texture_n, data->mlx.mlx);
}

static t_texture	*load_texture(char *path, void *mlx)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		free(texture);
		return (NULL);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(mlx, texture->img);
		free(texture);
		return (NULL);
	}
	return (texture);
}

static void	unload_texture(t_texture *texture, void *mlx)
{
	mlx_destroy_image(mlx, texture->img);
	free(texture);
}
