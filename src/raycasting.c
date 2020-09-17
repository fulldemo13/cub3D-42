/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:32:27 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:19:27 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_init(t_params *p)
{
	p->raypos = vec(p->pos.x, p->pos.y);
	p->raydir = vec(p->dir.x + p->plane.x * p->camerax,
	p->dir.y + p->plane.y * p->camerax);
	p->map = vecint((int)p->raypos.x, (int)p->raypos.y);
	p->deltadist = vec(fabs(1 / p->raydir.x), fabs(1 / p->raydir.y));
	if (p->raydir.x < 0)
	{
		p->step.x = -1;
		p->sidedist.x = (p->raypos.x - p->map.x) * p->deltadist.x;
	}
	else
	{
		p->step.x = 1;
		p->sidedist.x = (p->map.x + 1.0 - p->raypos.x) * p->deltadist.x;
	}
	if (p->raydir.y < 0)
	{
		p->step.y = -1;
		p->sidedist.y = (p->raypos.y - p->map.y) * p->deltadist.y;
	}
	else
	{
		p->step.y = 1;
		p->sidedist.y = (p->map.y + 1.0 - p->raypos.y) * p->deltadist.y;
	}
}

void	raycasting_hit(t_params *p)
{
	while (p->hit == 0)
	{
		if (p->sidedist.x < p->sidedist.y)
		{
			p->sidedist.x += p->deltadist.x;
			p->map.x += p->step.x;
			p->side = 0;
		}
		else
		{
			p->sidedist.y += p->deltadist.y;
			p->map.y += p->step.y;
			p->side = 1;
		}
		if (p->worldmap[p->map.x][p->map.y] == 1)
			p->hit = 1;
	}
	if (p->side == 0)
		p->perpwalldist = (p->map.x - p->raypos.x +
		(1 - p->step.x) / 2) / p->raydir.x;
	else
		p->perpwalldist = (p->map.y - p->raypos.y +
		(1 - p->step.y) / 2) / p->raydir.y;
}

void	raycasting_side(t_params *p)
{
	p->lineheight = (int)(p->win_height / p->perpwalldist);
	p->drawstart = ((-1 * p->lineheight) / 2) + (p->win_height / 2);
	if (p->drawstart < 0)
		p->drawstart = 0;
	p->drawend = p->lineheight / 2 + p->win_height / 2;
	if (p->drawend >= p->win_height)
		p->drawend = p->win_height - 1;
	if (p->side == 0 && p->step.x == 1)
		p->texid = 0;
	else if (p->side == 0 && p->step.x == -1)
		p->texid = 1;
	else if (p->side == 1 && p->step.y == 1)
		p->texid = 2;
	else if (p->side == 1 && p->step.y == -1)
		p->texid = 3;
	if (p->side == 0)
		p->x_wall = p->pos.y + p->perpwalldist * p->raydir.y;
	else
		p->x_wall = p->pos.x + p->perpwalldist * p->raydir.x;
	p->x_wall -= floor(p->x_wall);
}

void	raycasting_draw(t_params *p, int x)
{
	p->texx = (int)(p->x_wall * (double)(p->tex[p->texid].texwidth));
	if (p->side == 0 && p->raydir.x > 0)
		p->texx = p->tex[p->texid].texwidth - p->texx - 1;
	if (p->side == 1 && p->raydir.y < 0)
		p->texx = p->tex[p->texid].texwidth - p->texx - 1;
	p->texx = abs(p->texx);
	while (p->drawstart < p->drawend)
	{
		p->texy = abs((((p->drawstart * 256 - p->win_height * 128 +
		p->lineheight * 128) * p->tex[p->texid].texheight) /
		p->lineheight) / 256);
		ft_memcpy(p->data_ptr + 4 * p->win_width * p->drawstart + x * 4,
		&p->tex[p->texid].data[(int)(p->texy % p->tex[p->texid].texheight *
		p->tex[p->texid].sizeline + p->texx % p->tex[p->texid].texwidth *
		p->tex[p->texid].bpp / 8)], sizeof(int));
		p->drawstart++;
	}
}

int		raycasting(t_params *p)
{
	int	x;

	x = 0;
	p->img_ptr = mlx_new_image(p->mlx_ptr, p->win_width, p->win_height);
	p->data_ptr = mlx_get_data_addr(p->img_ptr, &p->bits_per_pixel,
	&p->size_line, &p->endian);
	draw_sky(p);
	draw_floor(p);
	while (x < p->win_width)
	{
		p->camerax = 2 * x / (double)(p->win_width) - 1;
		raycasting_init(p);
		raycasting_hit(p);
		raycasting_side(p);
		raycasting_draw(p, x);
		p->zbuffer[x] = p->perpwalldist;
		p->hit = 0;
		x++;
	}
	calc_sprites(p);
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	mlx_destroy_image(p->mlx_ptr, p->img_ptr);
	return (0);
}
