#include "../cub3d.h"

int is_valid_char(char c)
{
    if (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '\n')
        return (1);
    return (0);
}
int is_player_dir(char c)
{
    if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
        return (1);
    return (0);
}
int check_map_charac(t_map *map)
{
    int i;
    int j;
    int player_flag;
    i = 0;
    player_flag = 0;
    while (i < map->map_height)
    {
        j = 0;
        while (j < map->map_width)
        {
            if (is_valid_char(map->grid[i][j]) == 0)
            {
                printf("ERROR\nInvalid charac in map----%c----\n", map->grid[i][j]);
                return (0);
            }
            if (is_player_dir(map->grid[i][j]))
            {
                if (player_flag)
                {
                    printf("ERROR\nMultiple players\n");
                    return (0);
                }
                player_flag = 1;
                map->player_x = j;
                map->player_y = i;
                map->player_dir = map->grid[i][j];
            }
            j++;
        }
        i++;
    }
    return (player_flag);
}
int valid_cell(t_map *map, int y, int x)
{
    if (y == 0 || y == map->map_height - 1 || x == 0 || x == map->map_width - 1)
    {
        if (map->grid[y][x] == '0' || is_player_dir(map->grid[y][x]))
            return (0);
    }
    if (map->grid[y][x] == '0' || is_player_dir(map->grid[y][x]))
    {
        if (y > 0 && map->grid[y - 1][x] == ' ')
        {
            printf("zainab4\n");

            return (0);
        }
        if (y < map->map_height - 1 && map->grid[y + 1][x] == ' ')
        {
            printf("zainab3\n");
            return (0);
        }
        if (x > 0 && map->grid[y][x - 1] == ' ')
        {
            printf("zainab2\n");
            return (0);
        }
        if (x < map->map_width - 1 && map->grid[y][x + 1] == ' ')
        {
            printf("zainab\n");
            return (0);
        }
    }
    return (1);
}
int check_walls(t_map *map)
{
    int (y),x;
    y = 0;
    while (y < map->map_height)
    {
        x = 0;
        while (x < map->map_width)
        {
            if (!valid_cell(map, y, x))
            {
                printf("ERROR\nThe map must be closed/surrounded by walls\n");
                printf("ERROR at position [%d][%d] = '%c'\n", y, x, map->grid[y][x]);
                return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}