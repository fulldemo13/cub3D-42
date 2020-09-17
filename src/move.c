/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:23:09 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:19:01 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spawn_player(t_params *p)
{
	if (p->dirplayer == 'E')
	{
		p->key.right = 1;
		while (floor(p->dir.x) != 0 && floor(p->dir.y) != 1)
			press_key(p);
		p->key.right = 0;
	}
	if (p->dirplayer == 'W')
	{
		p->key.left = 1;
		while (floor(p->dir.x) != 0 && floor(p->dir.y) != 1)
			press_key(p);
		p->key.left = 0;
	}
	if (p->dirplayer == 'S')
	{
		p->key.left = 1;
		while (floor(p->dir.x) != 0 || floor(p->dir.y) != 0)
			press_key(p);
		p->key.left = 0;
	}
}

void	rotate_rigth(t_params *p)
{
	if (p->key.right == 1)
	{
		p->oldir = p->dir.x;
		p->dir.x = p->dir.x * cos(-p->rotspeed) -
		p->dir.y * sin(-p->rotspeed);
		p->dir.y = p->oldir * sin(-p->rotspeed) +
		p->dir.y * cos(-p->rotspeed);
		p->oldplane = p->plane.x;
		p->plane.x = p->plane.x * cos(-p->rotspeed) -
		p->plane.y * sin(-p->rotspeed);
		p->plane.y = p->oldplane * sin(-p->rotspeed) +
		p->plane.y * cos(-p->rotspeed);
	}
}

void	rotate_left(t_params *p)
{
	if (p->key.left == 1)
	{
		p->oldir = p->dir.x;
		p->dir.x = p->dir.x * cos(p->rotspeed) -
		p->dir.y * sin(p->rotspeed);
		p->dir.y = p->oldir * sin(p->rotspeed) +
		p->dir.y * cos(p->rotspeed);
		p->oldplane = p->plane.x;
		p->plane.x = p->plane.x * cos(p->rotspeed) -
		p->plane.y * sin(p->rotspeed);
		p->plane.y = p->oldplane * sin(p->rotspeed) +
		p->plane.y * cos(p->rotspeed);
	}
}

void	move_frontback(t_params *p)
{
	if (p->key.up == 1 || p->key.w == 1)
	{
		if (p->worldmap[(int)(p->pos.x + p->dir.x *
		p->movespeed)][(int)(p->pos.y)] == 0)
			p->pos.x += p->dir.x * p->movespeed;
		if (p->worldmap[(int)(p->pos.x)][(int)(p->pos.y + p->dir.y *
		p->movespeed)] == 0)
			p->pos.y += p->dir.y * p->movespeed;
	}
	if (p->key.down == 1 || p->key.s == 1)
	{
		if (p->worldmap[(int)(p->pos.x - p->dir.x *
		p->movespeed)][(int)(p->pos.y)] == 0)
			p->pos.x -= p->dir.x * p->movespeed;
		if (p->worldmap[(int)(p->pos.x)][(int)(p->pos.y - p->dir.y *
		p->movespeed)] == 0)
			p->pos.y -= p->dir.y * p->movespeed;
	}
}

void	move_leftrigth(t_params *p)
{
	if (p->key.d == 1)
	{
		if (p->worldmap[(int)(p->pos.x + p->dir.y *
		p->movespeed)][(int)(p->pos.y)] == 0)
			p->pos.x += p->dir.y * p->movespeed;
		if (p->worldmap[(int)(p->pos.x)][(int)(p->pos.y - p->dir.x *
		p->movespeed)] == 0)
			p->pos.y -= p->dir.x * p->movespeed;
	}
	if (p->key.a == 1)
	{
		if (p->worldmap[(int)(p->pos.x - p->dir.y *
		p->movespeed)][(int)(p->pos.y)] == 0)
			p->pos.x -= p->dir.y * p->movespeed;
		if (p->worldmap[(int)(p->pos.x)][(int)(p->pos.y + p->dir.x *
		p->movespeed)] == 0)
			p->pos.y += p->dir.x * p->movespeed;
	}
}
