/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 08:19:51 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:15:13 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_width(t_params *p, t_draws *d, int y, int x)
{
	while (x < p->win_width)
	{
		d->cell = vecint((int)d->floor.x, (int)d->floor.y);
		d->te.x = (int)(p->tex[p->texid].texwidth * (d->floor.x - d->cell.x));
		d->te.y = (int)(p->tex[p->texid].texheight * (d->floor.y - d->cell.y));
		ft_memcpy(p->data_ptr + 4 * p->win_width * y + x * 4,
		&p->tex[p->texid].data[(int)((int)abs(d->te.y) %
		p->tex[p->texid].texheight * p->tex[p->texid].sizeline +
		(int)abs(d->te.x) % p->tex[p->texid].texwidth
		* p->tex[p->texid].bpp / 8)], sizeof(int));
		d->floor = vec((d->floor.x + d->floorstep.x),
		(d->floor.y + d->floorstep.y));
		x++;
	}
}

void	calc_heigth_floor(t_params *p, t_draws *d, int y, int h)
{
	int x;

	while (y < h)
	{
		x = 0;
		d->raydirx0 = vec((p->dir.x - p->plane.x), (p->dir.y - p->plane.y));
		d->raydirx1 = vec((p->dir.x + p->plane.x), (p->dir.y + p->plane.y));
		d->cp = y - p->win_height / 2;
		d->posz = 0.5 * p->win_height;
		d->rowdistance = d->posz / d->cp;
		d->floorstep.x = d->rowdistance * (d->raydirx1.x - d->raydirx0.x)
		/ p->win_width;
		d->floorstep.y = d->rowdistance * (d->raydirx1.y - d->raydirx0.y)
		/ p->win_width;
		d->floor.x = p->pos.x + d->rowdistance * d->raydirx0.x;
		d->floor.y = p->pos.y + d->rowdistance * d->raydirx0.y;
		calc_width(p, d, y, x);
		y++;
	}
}

void	calc_heigth_sky(t_params *p, t_draws *d, int y, int h)
{
	int x;

	while (y < h)
	{
		x = 0;
		d->raydirx0 = vec((p->dir.x - p->plane.x), (p->dir.y - p->plane.y));
		d->raydirx1 = vec((p->dir.x + p->plane.x), (p->dir.y + p->plane.y));
		d->cp = y - p->win_height / 2;
		d->posz = 0.5 * p->win_height;
		d->rowdistance = d->posz / d->cp;
		d->floorstep.x = d->rowdistance * (d->raydirx1.x - d->raydirx0.x)
		/ p->win_width;
		d->floorstep.y = d->rowdistance * (d->raydirx1.y - d->raydirx0.y)
		/ p->win_width;
		d->floor.x = -p->pos.x + d->rowdistance * d->raydirx0.x;
		d->floor.y = -p->pos.y + d->rowdistance * d->raydirx0.y;
		calc_width(p, d, y, x);
		y++;
	}
}

void	draw_floor(t_params *p)
{
	int		y;
	t_draws	*d;

	if (!(d = (t_draws *)malloc(sizeof(t_draws))))
		error("failed malloc");
	y = p->win_height / 2;
	p->texid = 4;
	calc_heigth_floor(p, d, y, p->win_height);
	free(d);
}

void	draw_sky(t_params *p)
{
	int		y;
	t_draws	*d;

	if (!(d = (t_draws *)malloc(sizeof(t_draws))))
		error("failed malloc");
	y = 0;
	p->texid = 5;
	calc_heigth_sky(p, d, y, p->win_height / 2);
	free(d);
}
