#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
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

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= game->map_height ||
			ray->map_x < 0 || ray->map_x >= (int)ft_strlen(game->map[ray->map_y]))
			break ;
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->img.addr + (y * tex->img.line_len + x * (tex->img.bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int			y;
	int			color;
	t_texture	*tex;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			tex_y;

	y = 0;
	while (y < ray->draw_start)
		my_mlx_pixel_put(&game->img, x, y++, game->ceiling_color);
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= (int)wall_x;
	if (ray->side == 0 && ray->dir_x > 0)
		tex = &game->tex_east;
	else if (ray->side == 0 && ray->dir_x < 0)
		tex = &game->tex_west;
	else if (ray->side == 1 && ray->dir_y > 0)
		tex = &game->tex_south;
	else
		tex = &game->tex_north;
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = get_texture_color(tex, tex_x, tex_y);
		my_mlx_pixel_put(&game->img, x, y++, color);
	}
	while (y < WIN_HEIGHT)
		my_mlx_pixel_put(&game->img, x, y++, game->floor_color);
}

void	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall_distance(&ray, game);
		draw_wall(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}