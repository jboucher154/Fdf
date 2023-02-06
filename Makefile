# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 17:07:53 by jebouche          #+#    #+#              #
#    Updated: 2023/02/06 17:08:19 by jebouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIB = libft/libft.a

SRCS = main.c draw_line.c mlx_close.c handle_press.c new_fdf.c get_map.c \
	 get_camera_view.c draw_camera_view.c new_camera.c line_utility.c

OBJS = $(SRCS:.c=.o)

DEPS = includes/fdf.h

CC = cc

CFLAGS = -Wall -Werror -Wextra -I. -Iincludes -Ilibft/includes

DEBUG_SANI = -g -fsanitize=address

DEBUG = -g

MLX_COMPILE = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_COMPILE) $(LIB) -o $(NAME)

%.o : %.c $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB) : 
	@$(MAKE) -C libft

clean: 
	@$(MAKE) clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@$(MAKE) fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
