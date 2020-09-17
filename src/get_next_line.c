/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalazon <cpalazon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 02:46:26 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/20 17:30:37 by cpalazon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	new_line(char **s, char **line, int len)
{
	char	*tmp;

	if ((*s)[len] == '\n')
	{
		*line = ft_strndup(*s, len);
		tmp = ft_strndup(&((*s)[len + 1]), ft_strlen(&((*s)[len + 1])));
		free(*s);
		*s = tmp;
	}
	else
	{
		*line = *s;
		*s = NULL;
		return (0);
	}
	return (1);
}

static int	check_line(char **s, char **line, int r, int fd)
{
	int		len;

	len = 0;
	if (r < 0)
		return (-1);
	else if (r == 0 && s[fd] == NULL)
	{
		*line = ft_strndup("", 1);
		return (0);
	}
	else
	{
		while (s[fd][len] != '\n' && s[fd][len] != '\0')
			len++;
		return (new_line(&s[fd], line, len));
	}
}

int			get_next_line(const int fd, char **line)
{
	int			r;
	static char	*s[4096];
	char		buff[128 + 1];
	char		*tmp;

	if (fd < 0 || line == NULL || 128 <= 0)
		return (-1);
	while ((r = read(fd, buff, 128)) > 0)
	{
		buff[r] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strndup(buff, ft_strlen(buff));
		else
		{
			tmp = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	return (check_line(s, line, r, fd));
}
