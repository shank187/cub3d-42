NAME        = cub3D
CC          = cc -g
CFLAGS      = -Wall -Wextra -Werror -g #-fsanitize=address# -I./minilibx-linux
MLX_FLAGS   = -L./minilibx-linux -lmlx -lXext -lX11 -lm -I./minilibx-linux

MAC_FLAGS  = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRCS        = raycasting.c \
              movment.c \
              textures.c \
              utils.c \
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
              parsing_utils_4.c \
              addons.c \
              parsing_flood.c \
              testing.c utils_door.c utils_minimap.c movment_utils.c raycasting_utils.c utils2.c utils3.c 

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MAC_FLAGS) -o $(NAME)

%.o: %.c cub.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
