NAME        = cub3D
CC          = cc -g
CFLAGS      = -Wall -Wextra -Werror -g #-fsanitize=address# -I./minilibx-linux
MLX_FLAGS   = -L./minilibx-linux -lmlx -lXext -lX11 -lm -I./minilibx-linux

MAC_FLAGS  = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRCS        = raycasting_bonus.c \
              movment_bonus.c \
              textures_bonus.c \
              utils_bonus.c \
              get_next_line_bonus.c \
              libft_0_bonus.c \
              libft_1_bonus.c \
              libft_2_bonus.c \
              libft_split_bonus.c \
              parsing_bonus.c \
              parsing_utils_0_bonus.c \
              parsing_utils_1_bonus.c \
              parsing_utils_2_bonus.c \
              parsing_utils_3_bonus.c \
              parsing_utils_4_bonus.c \
              addons_bonus.c \
              parsing_flood_bonus.c \
              testing_bonus.c utils_door_bonus.c utils_minimap_bonus.c movment_utils_bonus.c raycasting_utils_bonus.c utils2_bonus.c utils3_bonus.c 

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
