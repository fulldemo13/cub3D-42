/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:55:36 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:08:14 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector		vec(double x, double y)
{
	t_vector vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_vectorint		vecint(int x, int y)
{
	t_vectorint vectorint;

	vectorint.x = x;
	vectorint.y = y;
	return (vectorint);
}

int				exit_game(void)
{
	exit(1);
	return (0);
}

void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t		i;
	char		*str1;
	const char	*str2;

	i = 0;
	str1 = s1;
	str2 = s2;
	while (s1 == s2 || !n)
		return (s1);
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (s1);
}

int				ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	int				r;
	unsigned char	*s1_char;
	unsigned char	*s2_char;

	i = 0;
	r = 0;
	s1_char = (unsigned char *)s1;
	s2_char = (unsigned char *)s2;
	while (s1_char[i] != '\0' || s2_char[i] != '\0')
	{
		if (s1_char[i] != s2_char[i])
		{
			r = s1_char[i] - s2_char[i];
			if (r > 0)
			{
				return (1);
			}
			return (-1);
		}
		i++;
	}
	return (r);
}
