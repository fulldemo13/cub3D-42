/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcreator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:02:28 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:13:41 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_creator_column(t_params *p, char *line, int column)
{
	int	i;

	i = 0;
	if (column != 7)
		error("missing textures");
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			p->column++;
		i++;
	}
	free(line);
	line = NULL;
}

int		map_creator_check(t_params *p, char *line, int column)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'R')
		get_resolution(p, line);
	else if ((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S'
	&& line[i + 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E') ||
	(line[i] == 'E' && line[i + 1] == 'A') || line[i] == 'S' ||
	line[i] == 'F' || line[i] == 'C')
	{
		get_texture(p, line);
		column++;
	}
	else if (line[i] == '1')
		p->row++;
	return (column);
}

void	map_creator(char **argv, t_params *p)
{
	char	*line;
	int		r;
	int		fd;
	int		column;
	int		mapstart;

	column = 0;
	mapstart = 0;
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return ;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		column = map_creator_check(p, line, column);
		mapstart++;
		free(line);
		line = NULL;
	}
	if (line[0] == '1')
		p->row++;
	mapstart++;
	map_creator_column(p, line, column);
	close(fd);
	malloc_map(argv, p, mapstart);
}
