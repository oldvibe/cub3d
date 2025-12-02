#include "cub3d.h"

int pars_no(t_gc *gc, char *line, t_data *data)
{
    if (data->NO_flag)
    {
        printf("ERROR\nNO existe plusieurs fois\n");
        return (0);
    }
    data->NO_flag = 1;
    return (check_textures(gc, ft_strtrim(gc, line + 3, " \t"), &data->north_tex));
}

int pars_so(t_gc *gc, char *line, t_data *data)
{
    if (data->SO_flag)
    {
        printf("ERROR\nSO existe plusieurs fois\n");
        return (0);
    }
    data->SO_flag = 1;
    return (check_textures(gc, ft_strtrim(gc, line + 3, " \t"), &data->south_tex));
}

int pars_ea(t_gc *gc, char *line, t_data *data)
{
    if (data->EA_flag)
    {
        printf("ERROR\nEA existe plusieurs fois\n");
        return (0);
    }
    data->EA_flag = 1;
    return (check_textures(gc, ft_strtrim(gc, line + 3, " \t"), &data->east_tex));
}

int pars_we(t_gc *gc, char *line, t_data *data)
{
    if (data->WE_flag)
    {
        printf("ERROR\nWE existe plusieurs fois\n");
        return (0);
    }
    data->WE_flag = 1;
    return (check_textures(gc, ft_strtrim(gc, line + 3, " \t"), &data->west_tex));
}
int pars_c(char *line, t_data *data)
{
    if(data->c_flag)
    {
        printf("ERROR\nC exsite plusieurs fois\n");
        return(0);
    }
    data->c_flag = 1;
    return(pars_colors(data->gc, ft_strtrim(data->gc, line + 2, " \t"), &data->ceilling));
}
int pars_f(char *line , t_data *data)
{
    if(data->f_flag)
    {
        printf("ERROR\nF exsite plusieurs fois\n");
        return(0);
    }
    data->f_flag = 1;
    return(pars_colors(data->gc, ft_strtrim(data->gc,line + 2, " \t"), &data->floor));
}
int check_identifier(t_gc *gc, char *line, t_data *data)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        return (pars_no(gc, line, data));
    else if (ft_strncmp(line, "SO ", 3) == 0)
        return (pars_so(gc, line, data));
    else if (ft_strncmp(line, "WE ", 3) == 0)
        return (pars_we(gc, line, data));
    else if (ft_strncmp(line, "EA ", 3) == 0)
        return (pars_ea(gc, line, data));
    else if (ft_strncmp(line, "C ", 2) == 0)
        return (pars_c(line, data));
    else if (ft_strncmp(line, "F ", 2) == 0)
        return (pars_f(line, data));
    else
    {
        printf("ERROR\nUndefined identifier\n");
        return (0);
    }
}