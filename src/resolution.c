/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:57:43 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:10:03 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_resolution(t_params *p)
{
	if (p->win_width > 1920)
		p->win_width = 1920;
	if (p->win_height > 1080)
		p->win_height = 1080;
	if (p->win_width < 848)
		p->win_width = 848;
	if (p->win_height < 480)
		p->win_height = 480;
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr,
	p->win_width, p->win_height, "cub3d");
}

void	get_resolution(t_params *p, char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	p->win_width = 0;
	p->win_height = 0;
	while (line[i] != '\0')
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			while (line[i] >= '0' && line[i] <= '9')
			{
				if (flag == 0)
					p->win_width = p->win_width * 10 + (line[i] - '0');
				else
					p->win_height = p->win_height * 10 + (line[i] - '0');
				i++;
			}
			i--;
			flag++;
		}
		i++;
	}
	error_resolution(p);
}
