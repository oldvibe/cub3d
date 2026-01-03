/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-05 22:58:12 by yanait-e          #+#    #+#             */
/*   Updated: 2025-12-05 22:58:12 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	rotate_dir(t_player *p, double angle)
{
	double	old_dir_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
}

static void	rotate_plane(t_player *p, double angle)
{
	double	old_plane_x;

	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void	rotate_right(t_game *game)
{
	double	rot_speed;

	rot_speed = 0.015;
	rotate_dir(&game->player, rot_speed);
	rotate_plane(&game->player, rot_speed);
}

void	rotate_left(t_game *game)
{
	double	rot_speed;

	rot_speed = -0.015;
	rotate_dir(&game->player, rot_speed);
	rotate_plane(&game->player, rot_speed);
}
