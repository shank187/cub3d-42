/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:19:39 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/26 10:55:24 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>

# define BUFFER_SIZE 1000

typedef struct s_player
{
	double	x;
	double	y;
	char	dir;
	double	angle;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		is_valid;
}	t_map;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textures;

typedef struct s_game
{
	t_player		player;
	t_map			map;
	t_textures		textures;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}	t_game;

typedef struct s_gnl
{
	int		fd;
	int		i;
	char	*line;
	char	*tmp;
	t_game	*game;
}	t_gnl;


typedef struct s_split
{
	size_t		cols;
	char		**arr;
	char		c;
	const char	*s;
	t_game		*game;
}	t_split;

size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s1, t_game *game);
char			*ft_strchr(const char *s, int c);
int				ft_atoi(const char *str, int *i);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strjoin(char const *s1, char const *s2, t_game *game);
char			**ft_split(char const *s, char c, t_game *game);
char			*ft_substr(char const *s, unsigned int start, \
	size_t len, t_game *game);
void			flood_walls_check(char **arr, int i, int j, t_game *game);
char			*ft_strchr(const char *s, int c);
char			*get_next_line(int fd, t_game *game);
void			find_angle(t_game *game);
unsigned int	parse_color_rgb(char *line);
char			**parse_map(char *str, t_game *game);
void			ft_replace_chr(char *s, char **as, char target, char new_chr);
void			clean_parsing_stuff(t_game *game);
void			init_my_struct(t_game *game);
void			clean_parsing_stuff(t_game *game);
void			clean_data(t_game *game);
int				store_map_infos(t_game *game, char *line);
int				is_valid_extension(char *filename, char *identifier);
void			*extract_and_store_data(int fd, t_game *game);
void			show_data_strored(t_game *game); /////////////////////


#endif