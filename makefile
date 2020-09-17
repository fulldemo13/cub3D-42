# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/25 19:02:02 by fulldemo          #+#    #+#              #
#    Updated: 2020/09/17 13:28:08 by fulldemo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

SRC		= main.c \
		  get_next_line_utils.c \
		  get_next_line.c \
		  mapcreator.c \
		  errors.c \
		  screenshot.c \
		  drawskyfloor.c \
		  draw_sprite.c \
		  textures.c \
		  resolution.c \
		  check_map.c \
		  mapgenerator.c \
		  cub_utils.c \
		  keys.c \
		  move.c \
		  raycasting.c \

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
MLXDIR	= ./minilibx
MLX_LNK	= -lmlx -framework OpenGL -framework AppKit

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(MLX_INC) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:  fclean all clean obj re