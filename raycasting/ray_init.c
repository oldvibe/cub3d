#include "../cub3d.h"

static void	init_ray_direction(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	ray->dir_x = game->player.dir_x
		+ game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y
		+ game->player.plane_y * ray->camera_x;
}

static void	init_ray_map_position(t_game *game, t_ray *ray)
{
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->hit = 0;
}

static void	init_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

static void	init_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
	}
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	init_ray_direction(game, ray, x);
	init_ray_map_position(game, ray);
	init_delta_dist(ray);
	init_step_and_side_dist(game, ray);
}
