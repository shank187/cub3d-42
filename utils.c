#include "cub.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;
	size_t			i;

	i = 0;
	a = (unsigned char *)b;
	while (i < len)
	{
		a[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	error_exit(char *msg)
{
    printf("%s\n", msg);
    exit (1);
}

void clear_screen(t_game *g)
{
    int x;
    int y;

    y = 0;
    while (y < g->scr_h)
    {
        x = 0;
        while (x < g->scr_w)
        {
            if (y < g->scr_h / 2)
                pixel_put(&g->img, x, y, g->ceiling_color);  // Ceiling color
            else
                pixel_put(&g->img, x, y, g->floor_color); // Floor color
            x++;
        }
        y++;
    }
}
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

void open_the_door(t_game *game)
{
    int i = 0;
    int j;

    while (game->map.grid[i])
    {
        j = 0; // j = x , i = y
        while (game->map.grid[i][j])
        {
            if (game->map.grid[i][j] == '2' && 
                (((int)game->player.x == j && (int)game->player.y == i - 1) || 
                 ((int)game->player.x == j + 1 && (int)game->player.y == i - 1) || 
                 ((int)game->player.x == j + 1 && (int)game->player.y == i) ||
                 ((int)game->player.x == j + 1 && (int)game->player.y == i + 1) ||
                 ((int)game->player.x == j && (int)game->player.y == i + 1) ||
                 ((int)game->player.x == j - 1 && (int)game->player.y == i + 1) ||
                 ((int)game->player.x == j - 1 && (int)game->player.y == i) ||
                 ((int)game->player.x == j - 1 && (int)game->player.y == i - 1)))
            {
                game->map.grid[i][j] = '0';
            }
            j++;
        }
        i++;
    }
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
		mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	}
	return (0);
}

int	close_win(t_game *g)
{
	int	i;

	i = -1;
	while (++i < 5)
		if (g->texs[i].img)
			mlx_destroy_image(g->mlx, g->texs[i].img);
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	exit(0);
	return (0);
}