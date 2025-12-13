#include "../cub3d.h"

static int  load_texture(t_game *game, t_texture *tex, char *path)
{
    tex->img.img = mlx_xpm_file_to_image(game->mlx, path,
            &tex->width, &tex->height);
    if (!tex->img.img)
        return (0);
    tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bpp,
            &tex->img.line_len, &tex->img.endian);
    return (1);
}

static int  rgb_to_int(t_color *c)
{
    return ((c->r << 16) | (c->g << 8) | c->b);
}

static void setup_player_from_map(t_game *game, t_map *map)
{
    game->player.pos_x = map->player_x + 0.5;
    game->player.pos_y = map->player_y + 0.5;

    if (map->player_dir == 'N')
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
        game->player.plane_x = 0.66;
        game->player.plane_y = 0;
    }
    else if (map->player_dir == 'S')
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0;
    }
    else if (map->player_dir == 'E')
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = 0.66;
    }
    else if (map->player_dir == 'W')
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = -0.66;
    }
}

int parse_file(char *filename, t_game *game)
{
    t_data  data;
    t_map   *map;

    ft_memset(&data, 0, sizeof(t_data));
    data.gc = game->gc;

    if (!parsing1(game->gc, filename, &data, &map))
        return (0);

    // load textures using paths from t_data
    if (!load_texture(game, &game->tex_north, data.south_tex)
        || !load_texture(game, &game->tex_south, data.south_tex)
        || !load_texture(game, &game->tex_west, data.east_tex)
        || !load_texture(game, &game->tex_east, data.east_tex))
        return (0);

    // convert colors
    game->floor_color = rgb_to_int(&data.floor);
    game->ceiling_color = rgb_to_int(&data.ceilling);

    // connect the map to your t_game
    game->map = map->grid;
    game->map_width = map->map_width;
    game->map_height = map->map_height;

    // set player position + direction
    setup_player_from_map(game, map);

    return (1);
}
