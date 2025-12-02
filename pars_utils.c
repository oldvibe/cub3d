#include "cub3d.h"

int check_extension(char *filename)
{
    if(!filename)
        return(0);
    int len;
    len = ft_strlen(filename);
    if(len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
    {
        printf("ERROR\nThe extension must be .cub\n");
        return(0);
    }
    return(1);
}
int check_xpm_ext(char *path)
{
    if(!path)
        return(0);
    int len;
    len = ft_strlen(path);
    if(len < 4 ||  ft_strncmp(path + len -4, ".xpm", 4) != 0)
    {
        printf("ERROR\nThe extension for textures must be .xpm\n");
        return(0);
    }
    return(1);
}
int check_textures(t_gc *gc, char *line, char **texture)
{
    int fd;
    char *path;
    
    // path = gc_malloc(gc, ft_strlen(line) + 1);
    // if (!path)
    //     return (0);
    // ft_strcpy(path, ft_strtrim(gc,line, "\t\n"));
    path = ft_strtrim(gc, line, "\t\n ");
    if (!path || ft_strlen(path) == 0)
    {
        printf("ERROR\nThe path is empty\n");
        return (0);
    }
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        printf("ERROR\nCan not open the file\n");
        return (0);
    }
    close(fd);
    
    if (!check_xpm_ext(path))
        return (0);
    
    *texture = path;
    return (1);
}
int check_coma(char *str)
{
    int i;
    i = 0;
    while(str[i])
    {
        if(str[i] == ',' && str[i + 1] == ',')
            return(0);
        i++;
    }
    return(1);
}
int pars_colors(t_gc *gc, char *line, t_color *color)
{
    char **rgb_path;
    int i;
    
    line = ft_strtrim(gc, line, "\t\n");
    if (!line)
        return (0);
    if (!check_coma(line))
    {
        printf("ERROR\nThe structure of color %s is invalid\n", line);
        return (0);
    }
    
    rgb_path = ft_split(gc, line, ',');
    if (!rgb_path)
        return (0);
    
    i = 0;
    while (rgb_path[i])
        i++;
    if (i != 3)
    {
        printf("ERROR\nThe color must have 3 values R,G,B\n");
        return (0);
    }
    
    color->r = pars_rgb_value(gc, rgb_path[0]);
    color->g = pars_rgb_value(gc, rgb_path[1]);
    color->b = pars_rgb_value(gc, rgb_path[2]);
    
    if (color->r == -1 || color->g == -1 || color->b == -1)
        return (0);
    return (1);
}

int pars_rgb_value(t_gc *gc, char *rgb_val)
{
    int i;
    int value;
    i = 0;
    rgb_val = ft_strtrim(gc, rgb_val, "\n\t");
    while(rgb_val[i])
    {
        if(rgb_val[i] < '0' || rgb_val[i] > '9')
            return(-1);
        i++;
    }
    value = ft_atoi(rgb_val);
    if(value < 0 || value > 255)
    {
        printf("ERROR\nTHe value of color must be betweeb 0 and 255\n");
        return(-1);
    }
    return(value);
}