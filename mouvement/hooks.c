/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-03 03:52:08 by yanait-e          #+#    #+#             */
/*   Updated: 2026-01-03 03:52:08 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_keyrelease(int keycode, t_game *game)
{
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
