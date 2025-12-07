/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-05 22:43:32 by yanait-e          #+#    #+#             */
/*   Updated: 2025-12-05 22:43:32 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_lines(char *filename)
{
	int		fd;
	int		counter;
	char	*line;
	t_gc	*temp_gc;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	temp_gc = gc_init();
	if (!temp_gc)
	{
		close(fd);
		return (-1);
	}
	counter = 0;
	line = get_next_line(fd, temp_gc);
	while (line != NULL)
	{
		counter++;
		line = get_next_line(fd, temp_gc);
	}
	close(fd);
	gc_free_all(temp_gc);
	return (counter);
}

char	**read_lines(t_gc *gc, char *filename)
{
	int		fd;
	int		total_lines;
	int		i;
	char	**lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	total_lines = file_lines(filename);
	if (total_lines <= 0)
	{
		close(fd);
		return (NULL);
	}
	lines = gc_malloc(gc, sizeof(char *) * (total_lines + 1));
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd, gc);
	while (line != NULL)
	{
		lines[i] = line;
		i++;
		line = get_next_line(fd, gc);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

void	error_exit(t_game *game, char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	if (game && game->gc)
		gc_free_all(game->gc);
	exit(1);
}

int	exit_game(t_game *game)
{
	if (game->tex_north.img.img)
		mlx_destroy_image(game->mlx, game->tex_north.img.img);
	if (game->tex_south.img.img)
		mlx_destroy_image(game->mlx, game->tex_south.img.img);
	if (game->tex_west.img.img)
		mlx_destroy_image(game->mlx, game->tex_west.img.img);
	if (game->tex_east.img.img)
		mlx_destroy_image(game->mlx, game->tex_east.img.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->gc)
		gc_free_all(game->gc);
	exit(0);
	return (0);
}

static void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->gc = gc_init();
	if (!game->gc)
		error_exit(NULL, "Failed to initialize garbage collector");
	game->floor_color = -1;
	game->ceiling_color = -1;
}

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit(game, "Failed to initialize MLX");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		error_exit(game, "Failed to create window");
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
		error_exit(game, "Failed to create image");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
		return (1);
	}
	init_game(&game);
	init_mlx(&game);
	if (!parse_file(argv[1], &game))
		error_exit(&game, "Failed to parse file");
	raycasting(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.win, 17, 1L << 17, exit_game, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
