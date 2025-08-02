/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:19:39 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/02 11:22:10 by aelbour          ###   ########.fr       */
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
#include <stdint.h>
#include "mlx.h"
# include <math.h>
#include <stdbool.h>

// # include <string.h>
# include <errno.h>


# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOV_SPEED 0.05
# define ROT_SPEED 0.03
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 100
# define KEY_S 115
# define KEY_D 97
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define BUFFER_SIZE 1000



typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;



typedef struct s_player
{
	double	x;
	double	y;
	char	dir;
	double	angle;
	
	//exe
	
	// double	pos_x;
	// double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	start_dir;
}	t_player;


typedef struct s_ray {
	bool	door;
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	int		side;
	double	wall_dist;
	int		line_h;
	int		draw_s;
	int		draw_e;
	double	wall_x;
	int		tex_x;
	int		tex_y;
}	t_ray;

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
	char	*door;
	// 
}	t_textures;

typedef struct s_game
{
	t_player		player;// p
	t_map			map;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	
	//
	
	void		*mlx;
	void		*win;
	t_img		img;
	// t_player	p;
	t_textures	tex;
	t_img		texs[5];
	// char		**map;
	int			map_w;
	int			map_h;
	int			scr_w;
	int			scr_h;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_l;
	int			key_r;
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
// void			find_angle(t_game *game);
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
void			ft_fix_sizes(char **arr, char c, t_game *game);
void			show_data_strored(t_game *game); /////////////////////

// double find_angle(char direction);
void	free_2d_arr(char **str);

void	init_game(t_game *g);
/* Raycasting */
void	raycast(t_game *g);
void	init_ray(t_game *g, t_ray *r, int x);
void	calc_ray_dir(t_game *g, t_ray *r);
void	calc_step(t_game *g, t_ray *r);
void	dda(t_game *g, t_ray *r);
void	calc_wall_dist(t_game *g, t_ray *r);
void	calc_wall_h(t_game *g, t_ray *r);
void	draw_line(t_game *g, t_ray *r, int x);

/* Rendering */
void	load_texs(t_game *g);
void	render(t_game *g);
void	pixel_put(t_img *img, int x, int y, int color);

/* Input */
int		key_press(int key, t_game *g);
int		key_release(int key, t_game *g);
int		game_loop(t_game *g);
int		close_win(t_game *g);

/* Utils */

void	error_exit(char *msg);
void	*ft_memset(void *b, int c, size_t len);

/* movment*/
int		handle_movement(t_game *g, double move_speed);
int		handle_rotation(t_game *g, double rot_speed);

#endif