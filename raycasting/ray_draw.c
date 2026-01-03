/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-05 23:01:38 by yanait-e          #+#    #+#             */
/*   Updated: 2025-12-05 23:01:38 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->img.addr + (y * tex->img.line_len + x * (tex->img.bpp / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static t_texture	*select_texture(t_game *g, t_ray *r)
{
	if (r->side == 0 && r->dir_x > 0)
		return (&g->tex_east);
	if (r->side == 0 && r->dir_x < 0)
		return (&g->tex_west);
	if (r->side == 1 && r->dir_y > 0)
		return (&g->tex_south);
	return (&g->tex_north);
}

static double	get_wall_x(t_game *g, t_ray *r)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = g->player.pos_y + r->perp_wall_dist * r->dir_y;
	else
		wall_x = g->player.pos_x + r->perp_wall_dist * r->dir_x;
	return (wall_x - (int)wall_x);
}

static int	get_tex_x(t_ray *r, t_texture *t, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * t->width);
	if ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
		tex_x = t->width - tex_x - 1;
	return (tex_x);
}

static void	draw_column(t_game *g, t_ray *r, int x, t_texture *t)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	y = 0;
	while (y < r->draw_start)
		my_mlx_pixel_put(&g->img, x, y++, g->ceiling_color);
	tex_x = get_tex_x(r, t, get_wall_x(g, r));
	step = (double)t->height / r->line_height;
	tex_pos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2) * step;
	while (y <= r->draw_end)
	{
		tex_y = (int)tex_pos & (t->height - 1);
		tex_pos += step;
		my_mlx_pixel_put(&g->img, x, y++, get_texture_color(t, tex_x, tex_y));
	}
	while (y < WIN_HEIGHT)
		my_mlx_pixel_put(&g->img, x, y++, g->floor_color);
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	t_texture	*tex;

	if (ray->line_height <= 0)
		return ;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	tex = select_texture(game, ray);
	draw_column(game, ray, x, tex);
}
