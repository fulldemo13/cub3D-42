/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:31:36 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:05:29 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_edges(t_params *p, int i, int k, int flag)
{
	if (p->worldmap[0][k] != 1 || p->worldmap[p->row - 1][k] != 1 ||
	p->worldmap[i][0] != 1 || p->worldmap[i][p->column - 1] != 1)
		flag++;
	return (flag);
}

int		check_spriteposition(t_params *p, int i, int k, int flag2)
{
	if (p->worldmap[i][k] != 1 && p->worldmap[i][k] != 0)
	{
		if (p->worldmap[i][k] == 'S' || p->worldmap[i][k] == 'W' ||
		p->worldmap[i][k] == 'E' || p->worldmap[i][k] == 'N')
		{
			flag2++;
			check_positions(p, i, k);
		}
		else if (p->worldmap[i][k] == '2')
		{
			p->sprite_pos[p->numsprites] = vec(i, k);
			p->numsprites++;
		}
		else
			error("bad letter");
	}
	return (flag2);
}

void	check_map(t_params *p)
{
	int	i;
	int	k;
	int flag;
	int	flag2;

	flag = 0;
	flag2 = 0;
	i = 0;
	k = 0;
	while (i < p->row && flag == 0 && flag2 <= 1)
	{
		while (k < p->column)
		{
			flag += check_edges(p, i, k, flag);
			flag2 = check_spriteposition(p, i, k, flag2);
			k++;
		}
		k = 0;
		i++;
	}
	check_map_errors(flag, flag2);
}
