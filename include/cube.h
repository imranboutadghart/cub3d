
#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"
# include <math.h>
# include "minimap.h"
# include "colors.h"
# include "keys.h"

// general data
# define NAME "cub3D"
# define PI 3.14159265358979323846
# define EPSILON 0.00005

// game data
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define TILE_SIZE 64
# define FPS 30
# define FOV (60.0 * PI / 180)

// initialization
# define INIT_ROT_SPEED 1
# define INIT_DIR 0
# define INIT_WALK_SPEED 5

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
	int		cols;
	int		lines;
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
	int		x;
	int		y;
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
	int				cols;
	int				lines;
	int				floor_color;
	int				ceil_color;
	int				pressed_keys[KEYS_COUNT];
	t_ray			rays[WINDOW_WIDTH];
}	t_data;

// PARSING
t_parsing_data	*parse(int ac, char **av);
void	free_parsing_data(t_parsing_data *data);
void	free_map(char **map, int cols);

// DATA
//		MLX
int		init_mlx(t_data *data);
void	destroy_mlx(t_data *data);

//		TEXTURES
int		init_textures(t_parsing_data data, t_data *out);
void	destroy_textures(t_data *data);

// 		PLAYER
int		init_player(t_parsing_data data, t_data *out);

//		DATA
int		init_data(t_parsing_data data, t_data *out);
void	destroy_data(t_data *data);

int		close_all(t_data *data);

//hooks
int key_press(int keycode, t_data *data);
int	key_release(int	keycode, t_data *data);

int		game_loop(t_data *data);
int	game_pause(t_data *data);

//rendering
int draw_minimap(t_data *data);
int draw_line(t_data *data, t_coords start, t_coords end, int color);
int	equal(t_coords a, t_coords b);
void my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);

void	do_movement(t_data *data);

int	error(char *msg);

//utils
int	is_out(int x, int y, t_data *data);
void	normalize_angle(double *angle);
size_t	ft_strlen(char *msg);
char	*ft_strdup(char *str);
void	*ft_memdup(void *src, size_t size);


#endif // CUBE_H