/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-03 03:51:28 by yanait-e          #+#    #+#             */
/*   Updated: 2026-01-03 03:51:28 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_find(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(t_gc *gc, char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	len;
	size_t	j;

	if (!s1 || !set || !gc)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	while (s1[i] && ft_find(set, s1[i]))
		i++;
	while (len > i && ft_find(set, s1[len - 1]))
		len--;
	res = (char *)gc_malloc(gc, sizeof(char) * (len - i + 1));
	if (res == NULL)
		return (NULL);
	j = 0;
	while (i < len)
	{
		res[j] = s1[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
