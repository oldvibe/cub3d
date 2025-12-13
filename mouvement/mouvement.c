/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-05 23:01:38 by yanait-e          #+#    #+#             */
/*   Updated: 2025-12-05 23:01:38 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_wall(t_game *g, double x, double y)
{
	if (g->map[(int)(y + PLAYER_R)][(int)x] == '1')
		return (1);
	if (g->map[(int)(y - PLAYER_R)][(int)x] == '1')
		return (1);
	if (g->map[(int)y][(int)(x + PLAYER_R)] == '1')
		return (1);
	if (g->map[(int)y][(int)(x - PLAYER_R)] == '1')
		return (1);
	return (0);
}

static void	try_move(t_game *g, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = g->player.pos_x + dx;
	ny = g->player.pos_y + dy;
	if (!is_wall(g, nx, ny))
	{
		g->player.pos_x = nx;
		g->player.pos_y = ny;
	}
}

void	move_forward(t_game *g)
{
	try_move(g, g->player.dir_x * MOVE_SPEED, g->player.dir_y * MOVE_SPEED);
}

void	move_backward(t_game *g)
{
	try_move(g, -g->player.dir_x * MOVE_SPEED, -g->player.dir_y * MOVE_SPEED);
}

void	move_left(t_game *g)
{
	try_move(g, -g->player.plane_x * MOVE_SPEED, -g->player.plane_y * MOVE_SPEED);
}

void	move_right(t_game *g)
{
	try_move(g, g->player.plane_x * MOVE_SPEED, g->player.plane_y * MOVE_SPEED);
}

static int	handle_move_keys(t_game *game)
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
	return (updated);
}

static int	handle_rotate_keys(t_game *game)
{
	int	updated;

	updated = 0;
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
	return (updated);
}

int	game_loop(t_game *game)
{
	int	updated;

	updated = 0;
	if (handle_move_keys(game))
		updated = 1;
	if (handle_rotate_keys(game))
		updated = 1;
	if (updated)
		raycasting(game);
	return (0);
}
