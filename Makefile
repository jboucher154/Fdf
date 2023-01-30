NAME = fdf

LIB = libft/libft.a

SRCS = main.c draw_line.c mlx_close.c handle_press.c new_fdf.c get_map.c \
	 camera.c draw_camera_view.c

OBJS = $(SRCS:.c=.o)

DEPS = fdf.h

CC = cc

CFLAGS = -Wall -Werror -Wextra -I.

DEBUG = -g -fsanitize=address

# MLX = -Imlx

MLX_COMPILE = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	$(CC) $(CFLAGS) $(DEBUG) -o $(NAME) $(OBJS) $(MLX_COMPILE) $(LIB)

%.o : %.c $(DEPS)
	@$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

clean: 
	$(MAKE) clean -C libft
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
