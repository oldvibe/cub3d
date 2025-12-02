#include "cub3d.h"

static char	*join_and_free(t_gc *gc, char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	result = gc_malloc(gc, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char	*get_next_line(int fd, t_gc *gc)
{
	char	*line;
	char	buffer[2];
	int		bytes;
	char	*temp;

	if (fd < 0)
		return (NULL);
	line = gc_malloc(gc, 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while ((bytes = read(fd, buffer, 1)) > 0)
	{
		buffer[bytes] = '\0';
		if (buffer[0] == '\n')
		{
			temp = join_and_free(gc, line, buffer);
			if (!temp)
				return (NULL);
			line = temp;
			break ;
		}
		temp = join_and_free(gc, line, buffer);
		if (!temp)
			return (NULL);
		line = temp;
	}
	if (bytes <= 0 && ft_strlen(line) == 0)
		return (NULL);
	return (line);
}