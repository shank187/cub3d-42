# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 12:00:00 by aelbour           #+#    #+#              #
#    Updated: 2025/08/24 14:15:42 by aelbour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

RM = rm -f

# Minilibx path (change this if your path is different)
MLX_DIR = mlx

# Source files for the mandatory part
MANDATORY_SRCS = \
	MANDATORY/addons.c \
	MANDATORY/get_next_line.c \
	MANDATORY/libft_0.c \
	MANDATORY/libft_1.c \
	MANDATORY/libft_2.c \
	MANDATORY/libft_split.c \
	MANDATORY/movment.c \
	MANDATORY/movment_utils.c \
	MANDATORY/parsing.c \
	MANDATORY/parsing_flood.c \
	MANDATORY/parsing_utils_0.c \
	MANDATORY/parsing_utils_1.c \
	MANDATORY/parsing_utils_2.c \
	MANDATORY/parsing_utils_3.c \
	MANDATORY/parsing_utils_4.c \
	MANDATORY/raycasting.c \
	MANDATORY/raycasting_utils.c \
	MANDATORY/textures.c \
	MANDATORY/utils.c \
	MANDATORY/utils2.c \
	MANDATORY/utils3.c \
	MANDATORY/utils_door.c 

# Source files for the bonus part
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

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME)

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(MLX_DIR) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I./ -c $< -o $@

clean:
	$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean

re: fclean all