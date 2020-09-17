/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:54:45 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:10:58 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

static void		set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

static int		get_color(t_params *p, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(p->data_ptr + (4 * (int)p->win_width *
	((int)p->win_height - 1 - y)) + (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int		write_bmp_header(int fd, int filesize, t_params *p)
{
	int				i;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	set_int_in_char(bmpfileheader + 18, p->win_width);
	set_int_in_char(bmpfileheader + 22, p->win_height);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

static int		write_bmp_data(int file, t_params *p, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					y;
	int					x;
	int					color;

	y = 0;
	while (y < (int)p->win_height)
	{
		x = 0;
		while (x < (int)p->win_width)
		{
			color = get_color(p, x, y);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void			screenshot(t_params *p)
{
	int file;
	int filesize;
	int	pad;

	pad = (4 - ((int)p->win_width * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)p->win_width + pad) * (int)p->win_height);
	file = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 777);
	write_bmp_header(file, filesize, p);
	write_bmp_data(file, p, pad);
	close(file);
	exit_game();
}
