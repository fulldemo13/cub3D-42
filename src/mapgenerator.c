/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapgenerator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:02:37 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:17:55 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_positions(t_params *p, int i, int k)
{
	if (p->worldmap[i][k] == 'S')
	{
		p->dirplayer = 'S';
		p->worldmap[i][k] = 0;
		p->pos = vec(i + 0.49, k + 0.49);
	}
	else if (p->worldmap[i][k] == 'W')
	{
		p->dirplayer = 'W';
		p->worldmap[i][k] = 0;
		p->pos = vec(i + 0.49, k + 0.49);
	}
	else if (p->worldmap[i][k] == 'E')
	{
		p->dirplayer = 'E';
		p->worldmap[i][k] = 0;
		p->pos = vec(i + 0.49, k + 0.49);
	}
	else if (p->worldmap[i][k] == 'N')
	{
		p->dirplayer = 'N';
		p->worldmap[i][k] = 0;
		p->pos = vec(i + 0.49, k + 0.49);
	}
}

void	fill_line_map(t_params *p, int i, char *line)
{
	int j;
	int	k;

	j = 0;
	k = 0;
	while (line[j] != '\0')
	{
		if (line[j] != ' ')
		{
			if (line[j] == '1' || line[j] == '0')
				p->worldmap[i][k] = line[j] - 48;
			else
				p->worldmap[i][k] = line[j];
			k++;
		}
		j++;
	}
	j = 0;
	k = 0;
}

void	fill_map(t_params *p, int fd, char *line, int mapstart)
{
	int i;

	i = 0;
	while (mapstart > p->row)
	{
		get_next_line(fd, &line);
		mapstart--;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	while (i < p->row)
	{
		get_next_line(fd, &line);
		fill_line_map(p, i, line);
		i++;
		free(line);
		line = NULL;
	}
	check_map(p);
}

void	malloc_map(char **argv, t_params *p, int mapstart)
{
	int		i;
	int		k;
	int		fd;
	char	*line;

	i = 0;
	k = 0;
	line = NULL;
	p->worldmap = (int **)malloc(sizeof(int*) * (p->row));
	if (p->worldmap == NULL)
		return ;
	while (i < p->row)
	{
		p->worldmap[i] = (int *)malloc(sizeof(int) * (p->column));
		if (p->worldmap[i] == NULL)
			return ;
		i++;
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return ;
	fill_map(p, fd, line, mapstart);
	close(fd);
}
