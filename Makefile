NAME = fdf

LIB = libft/libft.a

SRCS = main.c draw_line.c mlx_close.c handle_press.c new_fdf.c get_map.c \
	 get_camera_view.c draw_camera_view.c new_camera.c line_utility.c

OBJS = $(SRCS:.c=.o)

DEPS = fdf.h

CC = cc

CFLAGS = -Wall -Werror -Wextra -I.

# DEBUG = -g -fsanitize=address
DEBUG = -g

# MLX = -Imlx
MLX = -Lminilibx-linux -lmlx -L/usr/X11/include/../lib -lXext -lX11 -lm
X = /usr/X11/include/X11

MLX_COMPILE = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	$(CC) $(CFLAGS) $(DEBUG) -o $(NAME) $(OBJS) $(MLX_COMPILE) $(LIB) 
# $(CC) $(CFLAGS) $(DEBUG) -o $(NAME) $(OBJS) $(MLX) $(MLX_COMPILE) $(LIB) 

%.o : %.c $(DEPS)
	@$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@
# @$(CC) $(CFLAGS) $(DEBUG) -Iminilibx-linux -c $< -o $@

clean: 
	$(MAKE) clean -C libft
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
