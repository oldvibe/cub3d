#include "cub3d.h"

int is_line_empty(char *line)
{
    int i;
    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r')
            return (0);
        i++;
    }
    return (1);
}
int is_map_line(char *line)
{
    char *trimmed;
    
    if (!line || is_line_empty(line))
        return (0);
    
    trimmed = line;
    while (*trimmed == ' ' || *trimmed == '\t')
        trimmed++;
    if (*trimmed == '0' || *trimmed == '1' || *trimmed == ' ')
        return (1);
    return (0);
}

int start_map(char **lines, int total_lines, int *found_map)
{
    int i = 0;
    int counter = 0;
    char *trimmed;
    
    *found_map = 0;
    while (i < total_lines)
    {
        if (!lines[i] || is_line_empty(lines[i]))
        {
            i++;
            continue;
        }
        
        trimmed = lines[i];
        while (*trimmed == ' ' || *trimmed == '\t')
            trimmed++;
        if (ft_strncmp(trimmed, "NO ", 3) == 0 || 
            ft_strncmp(trimmed, "SO ", 3) == 0 || 
            ft_strncmp(trimmed, "WE ", 3) == 0 || 
            ft_strncmp(trimmed, "EA ", 3) == 0 || 
            ft_strncmp(trimmed, "F ", 2) == 0 || 
            ft_strncmp(trimmed, "C ", 2) == 0)
        {
            counter++;
        }
        if (counter == 6)
        {
            i++;
            while (i < total_lines && (ft_strlen(lines[i]) == 0 || is_line_empty(lines[i])))
                i++;
            
            if (i < total_lines && is_map_line(lines[i]))
            {
                *found_map = 1;
                return (i);
            }
            else
            {
                return (i);
            }
        }
        i++;
    }
    
    return (-1);
}

t_map *extract_map(t_gc *gc, char **lines, int total_lines)
{
    t_map *map;
    int i, j, len, start, found_map;
    
    if (!lines || !*lines)
    {
        printf("Error\nFichier vide ou invalide\n");
        return (NULL);
    }
    map = gc_malloc(gc, sizeof(t_map));
    if (!map)
        return (NULL);
    map->player_x = -1;
    map->player_y = -1;
    map->player_dir = 0;
    map->map_width = 0;
    map->grid = NULL;
    
    start = start_map(lines, total_lines, &found_map);
    if (start == -1)
    {
        printf("Error\nLes 6 éléments de configuration ne sont pas tous présents\n");
        return (NULL);
    }
    if (!found_map || start >= total_lines)
    {
        printf("Error\nLa map n'existe pas dans le fichier\n");
        return (NULL);
    }
    
    map->map_height = total_lines - start;
    if (map->map_height <= 0)
    {
        printf("Error\nLa map est vide\n");
        return (NULL);
    }
    
    i = start;
    while (i < total_lines)
    {
        len = ft_strlen(lines[i]);
        if (len == 0 || is_line_empty(lines[i]))
            return (NULL);
        if (len > map->map_width)
            map->map_width = len;
        i++;
    }
    
    map->grid = gc_malloc(gc, sizeof(char *) * (map->map_height + 1));
    if (!map->grid)
        return (NULL);
    
    i = 0;
    while (i < map->map_height)
    {
        map->grid[i] = gc_malloc(gc, sizeof(char) * (map->map_width + 1));
        if (!map->grid[i])
            return (NULL);
        
        j = 0;
        len = ft_strlen(lines[start + i]);
        if (len > 0 && lines[start + i][len - 1] == '\n')
            len--;
        
        while (j < len)
        {
            map->grid[i][j] = lines[start + i][j];
            j++;
        }
        while (j < map->map_width)
        {
            map->grid[i][j] = ' ';
            j++;
        }
        map->grid[i][map->map_width] = '\0';
        i++;
    }
    map->grid[i] = NULL;
    return (map);
}