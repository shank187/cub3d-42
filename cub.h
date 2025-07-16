/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:19:39 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/16 15:49:25 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H


# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

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
	t_player	player;
	t_map		map;
	t_textures	textures;
	t_rgb		floor_color;
	t_rgb		ceiling_color;
}	t_game;

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);


#endif