SRC = main.c frame_render.c key_actions.c mouse_actions.c tools.c render_scene.c vector_operations.c ft_atod.c
SRC += parsing/init_shape.c parsing/init.c parsing/parse_tool.c parsing/parse_utils.c parsing/parsing.c \
	parsing/process_parse.c parsing/stock_basic.c parsing/stock_plane.c parsing/stock_cylinder.c \
	parsing/stock_light.c parsing/stock_ambient.c parsing/stock_cam.c parsing/stock_sphere.c \
	parsing/stock_cone.c parsing/type.c parsing/valid.c

OBJ = $(SRC:.c=.o)
CFLAGS = -g3 #-Wall -Wextra -Werror

DEPS = $(SRC:.c=.d)

NAME = miniRT

minilibx = minilibx-linux/libmlx.a

libft = libft/libft.a

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
DEPS += $(GNL:.c=.d)
OBJ += $(GNL:.c=.o)

CC = cc

all: $(NAME)

$(minilibx):
	$(MAKE) -C minilibx-linux

$(libft):
	$(MAKE) -C libft bonus

$(NAME): $(minilibx) $(libft) $(OBJ)
	$(CC) $(OBJ) -I. -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -Llibft -lft -o $(NAME)

%.o: %.c
	$(CC) -c -MMD -MP -I. $(CFLAGS) $< -o $@

-include $(DEPS)

clean:
	$(MAKE) -C minilibx-linux clean
	$(MAKE) -C libft clean
	rm -f $(OBJ) $(DEPS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all
	$(MAKE) -C libft re

.PHONY: all clean fclean re
