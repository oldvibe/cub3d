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
