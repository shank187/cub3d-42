#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "mlx.h"

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

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	start_dir;
}	t_player;

typedef struct s_ray {
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

typedef struct s_tex {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceil;
}	t_tex;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	p;
	t_tex		tex;
	t_img		texs[4];
	char		**map;
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

/* Clear*/
void	clear_screen(t_game *g);

#endif