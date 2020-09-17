/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:03:19 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:12:35 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_sprites(t_params *p)
{
	int			i;
	t_vector	aux;

	i = 0;
	while (i < p->numsprites)
	{
		p->spritedistance[i] = ((p->pos.x - p->sprite_pos[i].x) *
		(p->pos.x - p->sprite_pos[i].x) + (p->pos.y - p->sprite_pos[i].y) *
		(p->pos.y - p->sprite_pos[i].y));
		i++;
		if (i > 0 && p->spritedistance[i] > p->spritedistance[i - 1])
		{
			aux = p->sprite_pos[i - 1];
			p->sprite_pos[i - 1] = p->sprite_pos[i];
			p->sprite_pos[i] = aux;
		}
	}
	i = 0;
	while (p->numsprites > i)
	{
		draw_sprite(p, i);
		i++;
	}
}

void	startend_sprite(t_params *p, t_sprite *s)
{
	s->drawstart.y = -s->spriteheight / 2 + p->win_height / 2;
	if (s->drawstart.y < 0)
		s->drawstart.y = 0;
	s->drawend.y = s->spriteheight / 2 + p->win_height / 2;
	if (s->drawend.y >= p->win_height)
		s->drawend.y = p->win_height - 1;
	s->spritewidth = abs((int)(p->win_height / s->transform.y));
	s->drawstart.x = -s->spritewidth / 2 + s->spritescreenx;
	if (s->drawstart.x < 0)
		s->drawstart.x = 0;
	s->drawend.x = s->spritewidth / 2 + s->spritescreenx;
	if (s->drawend.x >= p->win_width)
		s->drawend.x = p->win_width;
}

void	copybits_sprite(t_params *p, t_sprite *s)
{
	while (s->y < s->drawend.y)
	{
		s->d = (s->y) * 256 - p->win_height * 128 + s->spriteheight * 128;
		s->tex.y = ((s->d * p->tex[6].texheight) / s->spriteheight) / 256;
		if ((int)p->tex[6].data[s->tex.y % p->tex[6].texheight *
		p->tex[6].sizeline + s->tex.x % p->tex[6].texwidth *
			p->tex[6].bpp / 8] != 0)
			ft_memcpy(p->data_ptr + 4 * p->win_width * s->y + s->stripe *
			4, &p->tex[6].data[s->tex.y % p->tex[6].texheight *
			p->tex[6].sizeline + s->tex.x % p->tex[6].texwidth *
			p->tex[6].bpp / 8], sizeof(int));
		s->y++;
	}
}

void	drawimage_sprite(t_params *p, t_sprite *s)
{
	s->stripe = s->drawstart.x;
	while (s->stripe < s->drawend.x)
	{
		s->tex.x = (int)(256 * (s->stripe - (-s->spritewidth / 2 +
		s->spritescreenx)) * p->tex[6].texwidth / s->spritewidth) / 256;
		if (s->transform.y > 0 && s->stripe > 0 && s->stripe < p->win_width &&
		s->transform.y < p->zbuffer[s->stripe])
		{
			s->y = s->drawstart.y;
			copybits_sprite(p, s);
		}
		s->stripe++;
	}
}

void	draw_sprite(t_params *p, int i)
{
	t_vector	pos_sprite;
	double		invdet;
	t_sprite	*s;

	if (!(s = (t_sprite *)malloc(sizeof(t_sprite))))
		error("failed malloc");
	pos_sprite = vec(p->sprite_pos[i].x - p->pos.x + .5,
	p->sprite_pos[i].y - p->pos.y + .5);
	invdet = 1.0 / (p->plane.x * p->dir.y - p->dir.x * p->plane.y);
	s->transform = vec((invdet * (p->dir.y * pos_sprite.x - p->dir.x *
	pos_sprite.y)),
	(invdet * (-p->plane.y * pos_sprite.x + p->plane.x * pos_sprite.y)));
	s->spritescreenx = (int)((p->win_width / 2) * (1 + s->transform.x /
	s->transform.y));
	s->spriteheight = abs((int)(p->win_height / s->transform.y));
	startend_sprite(p, s);
	drawimage_sprite(p, s);
	free(s);
}
