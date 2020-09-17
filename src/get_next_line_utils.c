/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 02:48:38 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 12:53:43 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dst = malloc(sizeof(dst) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == NULL)
		return (NULL);
	while (*s1)
	{
		dst[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		dst[i] = *s2;
		i++;
		s2++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char*)s);
		s++;
	}
	if (*s == c)
		return ((char*)s);
	return (NULL);
}

char	*ft_strdup(char const *str)
{
	char	*cpy;
	int		i;

	if (!str)
		return (NULL);
	if (!(cpy = (char*)malloc(sizeof(*cpy) * (ft_strlen(str) + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

char	*ft_strndup(const char *s1, size_t len)
{
	size_t	i;
	char	*r;

	i = 0;
	while (s1[i] != '\0' && i < len)
		i++;
	r = malloc(i + 1);
	if (r == NULL)
	{
		return (0);
	}
	i = 0;
	while (s1[i] != '\0' && i < len)
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
