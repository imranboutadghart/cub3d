
#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"
# include <math.h>
# include "minimap.h"

# define NAME "cub3D"
# define TILE_SIZE 64
# define PI 3.14159265358979323846
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define FPS 30
# define FOV (60.0 * PI / 180)
# define EPSILON 0.0000005

# define UP	1
# define DOWN  2
# define LEFT  3
# define RIGHT 4
# define FACING_DOWN 0
# define FACING_UP 1
# define FACING_LEFT 2
# define FACING_RIGHT 3

# define SQUARE(x) ((x) * (x))

# define TEXTURE_E "assets/1.xpm"
# define TEXTURE_W "assets/2.xpm"
# define TEXTURE_S "assets/3.xpm"
# define TEXTURE_N "assets/4.xpm"

typedef struct s_parsing_data
{
	char	**map;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	int		f;
	int		c;
	int		player_x;
	int		player_y;
	int		width;
	int		height;
}	t_parsing_data;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
	double	rot_speed;
	double	walk_speed;

}	t_player;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}	t_mlx_data;

typedef struct s_texture_pack
{
	t_texture	*texture_e;
	t_texture	*texture_w;
	t_texture	*texture_s;
	t_texture	*texture_n;
}	t_texture_pack;

typedef struct s_ray
{
	double	angle;
	double	dist;
	t_coords	hit_x;
	t_coords	hit_y;
	t_coords	hit;
	int		hit_direction;
	int		x_texture_offset;
	int		y_texture_offset;
	int		texture_offset;
}	t_ray;

typedef struct s_data
{
	char			**map;
	t_texture_pack	textures;
	t_mlx_data		mlx;
	t_player		player;
	int				width;
	int				height;
	int				floor_color;
	int				ceil_color;
	t_ray			rays[WINDOW_WIDTH];
}	t_data;

// MLX
int		init_mlx(t_data *data);
void	destroy_mlx(t_data *data);
// TEXTURES
int		init_textures(t_parsing_data data, t_data *out);
void	destroy_textures(t_data *data);

t_parsing_data	parse(int ac, char **av);
char	**get_map(void);
void	free_map(char **map);
int		close_win(t_data *data);
int		init_data(t_parsing_data data, t_data *out);
int		init_player(t_parsing_data data, t_data *out);
int		game_loop(t_data *data);
void	destroy_data(t_data *data);

//hooks
int key_press(int keycode, t_data *data);

//rendering
int draw_minimap(t_data *data);
int draw_line(t_data *data, t_coords start, t_coords end);
int	equal(t_coords a, t_coords b);
void my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);

int	error(char *msg);

//utils
int	is_out(int x, int y, t_data *data);

#endif // CUBE_H