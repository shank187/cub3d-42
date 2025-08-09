NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -fsanitize=address -I./minilibx-linux
MLX_FLAGS   = -L./minilibx-linux -lmlx -lXext -lX11 -lm -I./minilibx-linux

MAC_FLAGS  = -Lmlx -lmlx -framework OpenGL -framework AppKit 

SRCS        = raycasting.c \
              movment.c \
              textures.c \
              utils.c \
              allocs.c \
              get_next_line.c \
              libft_0.c \
              libft_1.c \
              libft_2.c \
              libft_split.c \
              parsing.c \
              parsing_utils_0.c \
              parsing_utils_1.c \
              parsing_utils_2.c \
              parsing_utils_3.c \
              testing.c

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c cub.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
