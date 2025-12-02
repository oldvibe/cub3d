#include "cub3d.h"

int check_all_elements(t_data *data)
{
    if (!data->NO_flag)
        return (0);
    if (!data->SO_flag)
        return (0);
    if (!data->WE_flag)
        return (0);
    if (!data->EA_flag)
        return (0);
    if (!data->f_flag)
        return (0);
    if (!data->c_flag)
        return (0);
    return (1);
}
int count_elements(t_data *data)
{
    if (data->NO_flag && data->SO_flag && data->EA_flag && data->WE_flag && data->c_flag && data->f_flag)
        return (1);
    else
        return (0);
}
int pars_config_elem(t_gc *gc, char **lines, int total_lines, t_data *data)
{
    int i;
    char *trimmed;
    int config_counter = 0;
    
    i = 0;
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
        
        if (is_map_line(lines[i]))
        {
            if (config_counter != 6)
            {
                printf("ERROR\nMap structure is invalid\n");
                return (0);
            }
            break;
        }
        
        if (!check_identifier(gc, trimmed, data))
            return (0);
        
        config_counter++;
        i++;
    }
    return (1);
}
int parsing1(t_gc *gc, char *filename, t_data *data, t_map **map)
{
    char **lines;
    int total_lines;
    
    if (!check_extension(filename))
        return (0);
    
    total_lines = file_lines(filename);
    if (total_lines <= 0)
    {
        printf("The file is empty!\n");
        return (0);
    }
    
    lines = read_lines(gc, filename);
    if (!lines)
        return (0);
    
    if (!pars_config_elem(gc, lines, total_lines, data))
        return (0);
    
    if (!check_all_elements(data))
        return (0);
    
    *map = extract_map(gc, lines, total_lines);
    if (!*map)
    {
        printf("Map is invalid\n");
        return (0);
    }
    
    if (!check_map_charac(*map))
        return (0);
    
    if (!check_walls(*map))
        return (0);
    
    return (1);
}
