/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:02:51 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/25 19:14:18 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	params_initialice(t_params *p, char **argv)
{
	p->dir = vec(-1, 0);
	p->win_height = 488;
	p->win_width = 648;
	p->map_height = p->row;
	p->map_width = p->column;
	p->plane = vec(0, 0.66);
	p->key.w = 0;
	p->key.d = 0;
	p->key.a = 0;
	p->key.s = 0;
	p->key.right = 0;
	p->key.left = 0;
	p->key.up = 0;
	p->key.down = 0;
	p->row = 0;
	p->column = 0;
	p->numsprites = 0;
	map_creator(argv, p);
}

int		main(int argc, char **argv)
{
	t_params	*p;

	if (argc < 2)
		return (error("insert map"));
	if (!(p = (t_params *)malloc(sizeof(t_params))))
		return (0);
	params_initialice(p, argv);
	mlx_hook(p->win_ptr, 17, 0, exit_game, p);
	mlx_hook(p->win_ptr, 2, 0, key_press, p);
	mlx_hook(p->win_ptr, 3, 0, key_unpress, p);
	spawn_player(p);
	raycasting(p);
	if (argc >= 3)
	{
		if (argc == 3 && (ft_strcmp(argv[2], "--save") == 0))
			screenshot(p);
		error("bad arguments");
		exit_game();
	}
	mlx_loop_hook(p->mlx_ptr, press_key, p);
	mlx_loop(p->mlx_ptr);
	free(p);
	return (0);
}
