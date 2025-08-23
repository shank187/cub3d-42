#include "cub.h"

void	init_game(t_game *g)
{
	g->mlx = mlx_init();
	g->scr_w = SCREEN_WIDTH;
	g->scr_h = SCREEN_HEIGHT;
	g->horse.scale = 3;
	g->horse.height = 160 * g->horse.scale;
	g->horse.width = 160 * g->horse.scale;
	g->horse.pos_x = (SCREEN_WIDTH / 2) - (g->horse.width / 2);
	g->horse.pos_y = SCREEN_HEIGHT - g->horse.height + 50;
	g->horse.base_pos_y = SCREEN_HEIGHT - g->horse.height;
	g->horse.texture = "./textures/horse.xpm";
	g->win = mlx_new_window(g->mlx, g->scr_w, g->scr_h, "cub3D");
	g->img.img = mlx_new_image(g->mlx, g->scr_w, g->scr_h);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	g->horse.img = mlx_xpm_file_to_image(g->mlx, g->horse.texture,
			&g->horse.width, &g->horse.height);
	g->closed_door = NULL;
	g->key_w = 0;
	g->key_a = 0;
	g->key_s = 0;
	g->key_d = 0;
	g->key_l = 0;
	g->key_r = 0;
}

int	key_press(int key, t_game *g)
{
	if (key == KEY_ESC || key == 53)
		close_win(g);
	else if (key == KEY_W || key == MLX_KEY_W)
		g->key_w = 1;
	else if (key == KEY_A || key == MLX_KEY_A)
		g->key_a = 1;
	else if (key == KEY_S || key == MLX_KEY_S)
		g->key_s = 1;
	else if (key == KEY_D || key == MLX_KEY_D)
		g->key_d = 1;
	else if (key == KEY_LEFT || key == MLX_KEY_LEFT)
		g->key_l = 1;
	else if (key == KEY_RIGHT || key == MLX_KEY_RIGHT)
		g->key_r = 1;
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == KEY_W || key == MLX_KEY_W)
		g->key_w = 0;
	else if (key == KEY_A || key == MLX_KEY_A)
		g->key_a = 0;
	else if (key == KEY_S || key == MLX_KEY_S)
		g->key_s = 0;
	else if (key == KEY_D || key == MLX_KEY_D)
		g->key_d = 0;
	else if (key == KEY_LEFT || key == MLX_KEY_LEFT)
		g->key_l = 0;
	else if (key == KEY_RIGHT || key == MLX_KEY_RIGHT)
		g->key_r = 0;
	return (0);
}

void	mini_map(t_game *game)
{
	t_minimap	v;

	init_minimap(&v, game);
	draw_minimap_grid(game, &v);
	draw_player_dot(game, &v);
}

int	game_loop(t_game *g)
{
	double	move_speed;
	double	rot_speed;
	int		moved;

	move_speed = 0.05;
	rot_speed = 0.03;
	moved = 0;
	moved += handle_movement(g, move_speed);
	moved += handle_rotation(g, rot_speed);
	if (moved)
	{
		open_the_door(g);
		raycast(g);
		mini_map(g);
		animated_sprite(g);
		render_horse_sprite(g);
		mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	}
	return (0);
}
