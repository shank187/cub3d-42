#include "cub3d.h"


void	init_game(t_game *g)
{
	g->mlx = mlx_init();
	g->scr_w = SCREEN_WIDTH;
	g->scr_h = SCREEN_HEIGHT;
	g->win = mlx_new_window(g->mlx, g->scr_w, g->scr_h, "cub3D");
	g->img.img = mlx_new_image(g->mlx, g->scr_w, g->scr_h);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp,
			&g->img.line_len, &g->img.endian);
	g->key_w = 0;
	g->key_a = 0;
	g->key_s = 0;
	g->key_d = 0;
	g->key_l = 0;
	g->key_r = 0;
}

int	key_press(int key, t_game *g)
{
	if (key == KEY_ESC)
		close_win(g);
	else if (key == KEY_W)
		g->key_w = 1;
	else if (key == KEY_A)
		g->key_a = 1;
	else if (key == KEY_S)
		g->key_s = 1;
	else if (key == KEY_D)
		g->key_d = 1;
	else if (key == KEY_LEFT)
		g->key_l = 1;
	else if (key == KEY_RIGHT)
		g->key_r = 1;
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == KEY_W)
		g->key_w = 0;
	else if (key == KEY_A)
		g->key_a = 0;
	else if (key == KEY_S)
		g->key_s = 0;
	else if (key == KEY_D)
		g->key_d = 0;
	else if (key == KEY_LEFT)
		g->key_l = 0;
	else if (key == KEY_RIGHT)
		g->key_r = 0;
	return (0);
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
		clear_screen(g);
		raycast(g);
		mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	}
	return (0);
}

int	close_win(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (g->texs[i].img)
			mlx_destroy_image(g->mlx, g->texs[i].img);
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	g;

	// Hardcoded map data
	char *hardcoded_map[] = {
		"1111111111",
		"1000000001",
		"1010000101",
		"1111001001",
		"1000000001",
		"1111111111",
		NULL
	};

	(void)argc;
	(void)argv;
	
	// Initialize game with hardcoded values
	ft_memset(&g, 0, sizeof(t_game));
	g.map = hardcoded_map;
	g.map_w = 10;  // Width of the map
	g.map_h = 6;   // Height of the map
	
	// Player starting position and orientation
	g.p.pos_x = 2.5;
	g.p.pos_y = 2.5;
	g.p.dir_x = -1.0;  // Looking west
	g.p.dir_y = 0.0;
	g.p.plane_x = 0.0;
	g.p.plane_y = 0.66;  // Camera plane
	
	// Initialize game and textures
	init_game(&g);
	
	// Hardcode texture paths (make sure these files exist)
	g.tex.no = "./textures/north.xpm";
	g.tex.so = "./textures/south.xpm";
	g.tex.we = "./textures/west.xpm";
	g.tex.ea = "./textures/east.xpm";
	g.tex.floor = 0x8B4513;  // Brown
	g.tex.ceil = 0x87CEEB;   // Sky blue
	
	load_texs(&g);
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
	mlx_hook(g.win, 17, 0, close_win, &g);
	mlx_loop_hook(g.mlx, game_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
