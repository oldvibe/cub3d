#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * 0.05;
	new_y = game->player.pos_y + game->player.dir_y * 0.05;
	if (game->map[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	if (game->map[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * 0.05;
	new_y = game->player.pos_y - game->player.dir_y * 0.05;
	if (game->map[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	if (game->map[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.plane_x * 0.05;
	new_y = game->player.pos_y - game->player.plane_y * 0.05;
	if (game->map[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	if (game->map[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x * 0.05;
	new_y = game->player.pos_y + game->player.plane_y * 0.05;
	if (game->map[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
	if (game->map[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0.015;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed) - 
						game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + 
						game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed) - 
							game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + 
							game->player.plane_y * cos(rot_speed);
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = -0.015;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed) - 
						game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + 
						game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed) - 
							game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + 
							game->player.plane_y * cos(rot_speed);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	printf("DEBUG: Key released: %d\n", keycode);
	if (keycode == KEY_W || keycode == 119 || keycode == 13)
		game->key_w = 0;
	else if (keycode == KEY_S || keycode == 115 || keycode == 1)
		game->key_s = 0;
	else if (keycode == KEY_A || keycode == 97 || keycode == 0)
		game->key_a = 0;
	else if (keycode == KEY_D || keycode == 100 || keycode == 2)
		game->key_d = 0;
	else if (keycode == KEY_LEFT || keycode == 65361 || keycode == 123)
		game->key_left = 0;
	else if (keycode == KEY_RIGHT || keycode == 65363 || keycode == 124)
		game->key_right = 0;
	return (0);
}


int	handle_keypress(int keycode, t_game *game)
{
	printf("DEBUG: Key pressed: %d\n", keycode);
	if (keycode == KEY_ESC || keycode == 65307)
		exit_game(game);
	else if (keycode == KEY_W || keycode == 119 || keycode == 13)
		game->key_w = 1;
	else if (keycode == KEY_S || keycode == 115 || keycode == 1)
		game->key_s = 1;
	else if (keycode == KEY_A || keycode == 97 || keycode == 0)
		game->key_a = 1;
	else if (keycode == KEY_D || keycode == 100 || keycode == 2)
		game->key_d = 1;
	else if (keycode == KEY_LEFT || keycode == 65361 || keycode == 123)
		game->key_left = 1;
	else if (keycode == KEY_RIGHT || keycode == 65363 || keycode == 124)
		game->key_right = 1;
	return (0);
}


int	game_loop(t_game *game)
{
	int	updated;

	updated = 0;
	if (game->key_w)
	{
		move_forward(game);
		updated = 1;
	}
	if (game->key_s)
	{
		move_backward(game);
		updated = 1;
	}
	if (game->key_a)
	{
		move_left(game);
		updated = 1;
	}
	if (game->key_d)
	{
		move_right(game);
		updated = 1;
	}
	if (game->key_left)
	{
		rotate_left(game);
		updated = 1;
	}
	if (game->key_right)
	{
		rotate_right(game);
		updated = 1;
	}
	if (updated)
		raycasting(game);
	return (0);
}
