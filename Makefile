NAME        = cub3D
NAME_BONUS  = cub3D_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
MLX_FLAGS   = -Lmlx -lmlx -framework OpenGL -framework AppKit

# For Linux, uncomment the line below and comment the one above
# MLX_FLAGS   = -L./minilibx-linux -lmlx -lXext -lX11 -lm -I./minilibx-linux

MANDATORY_SRCS      = MANDATORY/raycasting.c \
            		 MANDATORY/movment.c \
            		 MANDATORY/textures.c \
            		 MANDATORY/utils.c \
            		 MANDATORY/get_next_line.c \
            		 MANDATORY/libft_0.c \
            		 MANDATORY/libft_1.c \
            		 MANDATORY/libft_2.c \
            		 MANDATORY/libft_split.c \
            		 MANDATORY/parsing.c \
            		 MANDATORY/parsing_utils_0.c \
            		 MANDATORY/parsing_utils_1.c \
            		 MANDATORY/parsing_utils_2.c \
            		 MANDATORY/parsing_utils_3.c \
            		 MANDATORY/parsing_utils_4.c \
            		 MANDATORY/addons.c \
            		 MANDATORY/parsing_flood.c \
            		 MANDATORY/utils_door.c \
            		 MANDATORY/movment_utils.c \
            		 MANDATORY/raycasting_utils.c \
            		 MANDATORY/utils2.c \
            		 MANDATORY/utils3.c

BONUS_SRCS = \
			BONUS/addons_bonus.c \
			BONUS/get_next_line_bonus.c \
			BONUS/libft_0__bonus.c \
			BONUS/libft_1_bonus.c \
			BONUS/libft_2_bonus.c \
			BONUS/libft_split_bonus.c \
			BONUS/movment_bonus.c \
			BONUS/movment_utils_bonus.c \
			BONUS/parsing_bonus.c \
			BONUS/parsing_flood_bonus.c \
			BONUS/parsing_utils_0_bonus.c \
			BONUS/parsing_utils_1_bonus.c \
			BONUS/parsing_utils_2_bonus.c \
			BONUS/parsing_utils_3_bonus.c \
			BONUS/parsing_utils_4_bonus.c \
			BONUS/raycasting_bonus.c \
			BONUS/raycasting_utils_bonus.c \
			BONUS/textures_bonus.c \
			BONUS/utils_bonus.c \
			BONUS/utils2_bonus.c \
			BONUS/utils3_bonus.c \
			BONUS/utils_door_bonus.c \
			BONUS/utils_minimap_bonus.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(MLX_FLAGS) -o $(NAME)

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(MLX_FLAGS) -o $(NAME_BONUS)

%.o: %.c MANDATORY/cub.h BONUS/cub_bonus.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean  all bonus

.PHONY: all clean fclean re