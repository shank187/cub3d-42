/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:19:39 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/22 13:11:11 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H


# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>


typedef struct s_player
{
	double	x;       // spawn position x (in pixels or tile coords)
	double	y;       // spawn position y
	char	dir;       // 'N', 'S', 'E', 'W'
	double	angle;   // direction converted to angle (in radians)
}	t_player;

typedef struct s_map
{
	char	**grid;    // the map as a 2D array
	int		width;
	int		height;
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

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str, int *i);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif