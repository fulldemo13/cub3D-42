/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 10:11:09 by fulldemo          #+#    #+#             */
/*   Updated: 2020/01/26 10:20:41 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct			s_vector
{
	double				x;
	double				y;
}						t_vector;
typedef struct			s_vectorint
{
	int					x;
	int					y;
}						t_vectorint;

typedef struct			s_key
{
	int					w;
	int					s;
	int					d;
	int					a;
	int					right;
	int					left;
	int					up;
	int					down;
}						t_key;

typedef struct			s_tex
{
	void				*img;
	char				*data;
	int					bpp;
	int					sizeline;
	int					endian;
	int					texwidth;
	int					texheight;
}						t_tex;

typedef struct			s_params
{
	void				*mlx_ptr;
	void				*win_ptr;
	char				*data_ptr;
	char				*tex_file;
	void				*data_pt;
	void				*img_ptr;
	t_vector			sprite_pos[500];
	int					numsprites;
	double				spritedistance[500];
	t_vector			pos;
	t_vector			raypos;
	t_vector			raydir;
	t_vector			dir;
	t_vector			plane;
	t_vector			sidedist;
	t_vector			deltadist;
	t_vectorint			map;
	t_vectorint			step;
	t_tex				tex[8];
	double				camerax;
	double				perpwalldist;
	double				movespeed;
	double				rotspeed;
	double				oldir;
	double				oldplane;
	double				wallx;
	double				texpos;
	double				zbuffer[4096];
	int					drawstart;
	int					texid;
	int					lineheight;
	int					drawend;
	int					win_width;
	int					win_height;
	int					map_width;
	int					map_height;
	int					hit;
	int					side;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_key				key;
	int					row;
	int					column;
	int					**worldmap;
	unsigned long int	**buffer;
	unsigned long int	uncolor;
	int					texwidth;
	int					texheight;
	double				x_wall;
	int					texx;
	int					texy;
	int					dirplayer;
}						t_params;

typedef struct			s_draws
{
	t_vector			raydirx0;
	t_vector			raydirx1;
	t_vector			floorstep;
	t_vector			floor;
	t_vectorint			cell;
	t_vectorint			te;
	int					cp;
	float				posz;
	float				rowdistance;
}						t_draws;

typedef struct			s_sprite
{
	t_vector			transform;
	int					spritescreenx;
	int					spriteheight;
	int					spritewidth;
	t_vectorint			drawstart;
	t_vectorint			drawend;
	t_vectorint			tex;
	int					stripe;
	int					y;
	int					d;
}						t_sprite;

typedef struct			s_bmp_header
{
	char				*flag;
	int					reserved;
	int					offset;
	int					file_size;
	int					planes;
	int					bit_per_pixel;
	int					compress;
	int					hr;
	int					vr;
	int					colors;
	int					important_color;
}						t_bmp_header;

typedef struct			s_bmp_encoder
{
	char				*buffer;
	int					width;
	int					height;
	int					extra_bytes;
	int					rgb_size;
	int					header_info_size;
	t_bmp_header		header;
	size_t				row_bytes;
	size_t				buffer_row_bytes;
}						t_bmp_encoder;

typedef struct			s_buffer
{
	size_t				length;
	char				*data;
}						t_buffer;

int						main(int argc, char **argv);
void					map_creator(char **argv, t_params *p);
t_vector				vec(double x, double y);
t_vectorint				vecint(int x, int y);
int						exit_game(void);
void					check_positions(t_params *p, int i, int k);
void					check_map(t_params *p);
void					malloc_map(char **argv, t_params *p, int mapstart);
void					fill_map(t_params *p, int fd, char *line, int mapstart);
void					check_map_errors(int flag, int flag2);
int						error(char *s);
void					screenshot(t_params *p);
int						raycasting(t_params *p);
void					*ft_memcpy(void *s1, const void *s2, size_t n);
void					draw_floor(t_params *p);
void					draw_sky(t_params *p);
void					draw_sprite(t_params *p, int i);
void					get_texture(t_params *p, char *line);
void					get_resolution(t_params *p, char *line);
int						ft_strcmp(const char *s1, const char *s2);
int						key_press(int key, t_params *p);
int						key_unpress(int key, t_params *p);
int						press_key(t_params *p);
void					rotate_rigth(t_params *p);
void					rotate_left(t_params *p);
void					move_frontback(t_params *p);
void					move_leftrigth(t_params *p);
void					calc_sprites(t_params *p);
void					spawn_player(t_params *p);

# define KEY_W 13
# define KEY_S 1
# define KEY_D 2
# define KEY_A 0
# define ESC 53
# define RIGHT 124
# define LEFT 123
# define DOWN 125
# define UP 126

#endif
