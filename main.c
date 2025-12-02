#include "cub3d.h"

#include "cub3d.h"

int file_lines(char *filename)
{
    int     fd;
    int     counter;
    char    *line;
    t_gc    *temp_gc;

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
char **read_lines(t_gc *gc, char *filename)
{
    int fd, total_lines, i;
    char **lines, *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    
    total_lines = file_lines(filename);
    lines = gc_malloc(gc, sizeof(char *) * (total_lines + 1));
    
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
// void init_data(t_data *data)
// {
//     data->north_tex = NULL;
//     data->south_tex = NULL;
//     data->east_tex = NULL;
//     data->west_tex = NULL;
//     data->NO_flag = 0;
//     data->SO_flag = 0;
//     data->EA_flag = 0;
//     data->WE_flag = 0;
//     data->f_flag = 0;
//     data->c_flag = 0;
//     data->floor.r = -1;
//     data->floor.g = -1;
//     data->floor.b = -1;
//     data->ceilling.r = -1;
//     data->ceilling.g = -1;
//     data->ceilling.b = -1;
// }

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

	mlx_hook(game.win, 2, 1L << 0, (int (*)())handle_keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, (int (*)())handle_keyrelease, &game);
	mlx_hook(game.win, 17, 1L << 17, (int (*)())exit_game, &game);
	mlx_loop_hook(game.mlx, (int (*)())game_loop, &game);
	
	mlx_loop(game.mlx);
	return (0);
}

