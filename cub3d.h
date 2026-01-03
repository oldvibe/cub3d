/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-03 03:51:36 by yanait-e          #+#    #+#             */
/*   Updated: 2026-01-03 03:51:36 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ============================== */
/*            INCLUDES            */
/* ============================== */

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "minilibx-linux/mlx.h"
# include "garbage_collector/garbage_colector.h"

/* ============================== */
/*            DEFINES             */
/* ============================== */

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define WIN_WIDTH 1280
# define WIN_HEIGHT 800

# define MOVE_SPEED 0.03
# define PLAYER_R 0.10

/* ============================== */
/*             KEYS               */
/* ============================== */

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

/* ============================== */
/*             STRUCTS            */
/* ============================== */

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_data
{
	int		NO_flag;
	int		SO_flag;
	int		WE_flag;
	int		EA_flag;
	int		f_flag;
	int		c_flag;

	char	*north_tex;
	char	*south_tex;
	char	*west_tex;
	char	*east_tex;

	t_color	floor;
	t_color	ceilling;

	t_gc	*gc;
}	t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	img;
	int		width;
	int		height;
}	t_texture;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;

	int		map_x;
	int		map_y;

	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;

	double	perp_wall_dist;

	int		step_x;
	int		step_y;
	int		hit;
	int		side;

	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;

	t_img		img;
	t_player	player;

	char		**map;
	int			map_width;
	int			map_height;

	t_texture	tex_north;
	t_texture	tex_south;
	t_texture	tex_west;
	t_texture	tex_east;

	int			floor_color;
	int			ceiling_color;

	t_gc		*gc;

	int			win_width;
	int			win_height;

	/* key states */
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left;
	int			key_right;
}	t_game;

/* ============================== */
/*            PARSING             */
/* ============================== */

int		parsing(t_gc *gc, char *filename, t_data *data, t_map **map);
int		parsing1(t_gc *gc, char *filename, t_data *data, t_map **map);
int		parse_file(char *filename, t_game *game);
int		parse_textures(char *line, t_game *game);

int		is_line_empty(char *line);
int		is_map_line(char *line);
int		check_identifier(t_gc *gc, char *line, t_data *data);
int		check_extension(char *filename);
int		file_lines(char *filename);

char	**read_lines(t_gc *gc, char *filename);
t_map	*extract_map(t_gc *gc, char **lines, int total_lines);

int		check_map_charac(t_map *map);
int		check_walls(t_map *map);

/* ============================== */
/*          RAYCASTING            */
/* ============================== */

void	raycasting(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_wall_distance(t_ray *ray, t_game *game);
void	draw_wall(t_game *game, t_ray *ray, int x);

/* ============================== */
/*        MOVEMENT & HOOKS        */
/* ============================== */

int		game_loop(t_game *game);

void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);

/* ============================== */
/*              UTILS             */
/* ============================== */

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		get_texture_color(t_texture *tex, int x, int y);

int		exit_game(t_game *game);
void	error_exit(t_game *game, char *msg);

/* ============================== */
/*          STRING UTILS          */
/* ============================== */

size_t	ft_strlen(const char *s);
char	*ft_strdup(t_gc *gc, const char *s);
char	*ft_substr(t_gc *gc, char const *s, unsigned int start, size_t len);
char	**ft_split(t_gc *gc, char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *b, int c, size_t len);
char	*get_next_line(int fd, t_gc *gc);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strtrim(t_gc *gc, char const *s1, char const *set);

int		pars_rgb_value(t_gc *gc, char *rgb_val);
int		check_textures(t_gc *gc, char *line, char **texture);
int		pars_colors(t_gc *gc, char *line, t_color *color);

#endif
