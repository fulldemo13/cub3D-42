/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:55:07 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:18:43 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choose_texture(t_params *p, char *pos)
{
	if (pos[0] == 'S' && pos[1] == 'O')
		p->texid = 0;
	else if (pos[0] == 'N' && pos[1] == 'O')
		p->texid = 1;
	else if (pos[0] == 'E' && pos[1] == 'A')
		p->texid = 2;
	else if (pos[0] == 'W' && pos[1] == 'E')
		p->texid = 3;
	else if (pos[0] == 'F')
		p->texid = 4;
	else if (pos[0] == 'C')
		p->texid = 5;
	else if (pos[0] == 'S')
		p->texid = 6;
	if (!(p->tex[p->texid].img = mlx_xpm_file_to_image(p->mlx_ptr,
	p->tex_file, &p->tex[p->texid].texwidth, &p->tex[p->texid].texheight)))
		error("bad texture");
	if (!(p->tex[p->texid].data = mlx_get_data_addr(p->tex[p->texid].img,
	&p->tex[p->texid].bpp, &p->tex[p->texid].sizeline,
	&p->tex[p->texid].endian)))
		error("bad texture");
	free(p->tex_file);
	free(pos);
}

void	get_texture(t_params *p, char *line)
{
	char	*pos;
	int		i;

	i = 0;
	if (!(pos = (char *)malloc(sizeof(char *) * 3)))
	{
		error("malloc failed");
		return ;
	}
	while (*line != ' ')
	{
		pos[i] = *line;
		line++;
		i++;
	}
	pos[i] = '\0';
	while (*line == ' ')
		line++;
	if (!(p->tex_file = ft_strdup(line)))
	{
		error("malloc failed");
		return ;
	}
	choose_texture(p, pos);
}
