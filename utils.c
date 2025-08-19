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

// calc_

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
    // if (!g->horse.img)
    //     error_exit("Failed to load horse texture");
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
	// printf("%i\n", key);
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

void add_door_to_end(t_door **head, int x, int y)
{
    t_door *new_door;
    t_door *current;
    
    new_door = malloc(sizeof(t_door));
    if (!new_door)
        return;
    new_door->x = x;
    new_door->y = y;
    new_door->next = NULL;
    if (*head == NULL)
    {
        *head = new_door;
        return;
    }
    current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = new_door;
}

void remove_door(t_door **head, int x, int y)
{
    t_door *current;
    t_door *prev;
     if (!head || *head == NULL)
        return;
    if ((*head)->x == x && (*head)->y == y)
    {
        current = *head;
        *head = (*head)->next;
        free(current);
        return;
    }
    prev = *head;
    current = (*head)->next;
    
    while (current != NULL)
    {
        if (current->x == x && current->y == y)
        {
            prev->next = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void open_the_door(t_game *game)
{
    int i = 0;
    int j;

    while (i < game->map_h)
    {
        j = 0; // j = x , i = y
        while (j < game->map_w)
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
				add_door_to_end(&game->closed_door, j, i);
            }
			else if (game->map.grid[i][j] == '0')
            {
                t_door *current = game->closed_door;
                int player_x = (int)game->player.x;
                int player_y = (int)game->player.y;
                
                while (current)
                {
                    if (current->x == j && current->y == i)
                    {
                        // Close door if player is far enough away
                        if (abs(player_x - j) > 1 || abs(player_y - i) > 1)
                        {
                            game->map.grid[i][j] = '2';
                            remove_door(&game->closed_door, j, i);
                            break;
                        }
                    }
                    current = current->next;
                }
            }
            j++;
        }
        i++;
    }
}


void free_all_doors(t_door **head)
{
    t_door *current;
    t_door *next;
    
    if (!head)
        return;
        
    current = *head;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void mini_map(t_game *game)
{
	int minimap_w = SCREEN_WIDTH / 8;
	int minimap_h = SCREEN_HEIGHT / 8;
	int start_x = SCREEN_WIDTH / 20;
	int start_y = SCREEN_HEIGHT / 20;
	int minigrid_w = minimap_w / game->map_w;
	int minigrid_h = minimap_h / game->map_h;
	if (minigrid_w < 1)
		minigrid_w = 1;
	if (minigrid_h < 1)
		minigrid_h = 1;	
	int map_y = 0;
	while (map_y < game->map_h)
	{
		int map_x = 0;
		while (map_x < game->map_w)
		{
			int screen_x = start_x + (map_x * minigrid_w);
			int screen_y = start_y + (map_y * minigrid_h);
			int color;
			if (game->map.grid[map_y][map_x] == '1')
				color = WALL_COLOR;
			else if (game->map.grid[map_y][map_x] == '2')
				color = DOOR_COLOR;
			else
				color = FLOOR_COLOR;
			
			int y = -1;
			while (++y < minigrid_h)
			{
				int x = -1;
				while (++x < minigrid_w)
				    pixel_put(&game->img, screen_x + x, screen_y + y, color);
			}
		
			map_x++;
		}
	    map_y++;
	}
	int player_screen_x = start_x + (int)(game->player.x * minigrid_w);
	int player_screen_y = start_y + (int)(game->player.y * minigrid_h);

	int dot_size = 2;
	int py = -2;
	while (py <= dot_size) // 5px
	{
	    int px = -2;
	    while (px <= dot_size) //5 px
	    {
	        pixel_put(&game->img, player_screen_x + px, player_screen_y + py, PLAYER_COLOR);
	        px++;
	    }
	    py++;
	}
}

void animated_sprite(t_game *game)
{
    static int frame = 0;
    static int dir = 1;
    int offset;

    if (frame >= 50) dir = -1;
    if (frame <= 0) dir = 1;

    frame += dir;                  // Move up/down in range [0,50]
    offset = frame / 2;            // Smaller movement speed
    game->horse.pos_y = game->horse.base_pos_y + offset;
}


void render_horse_sprite(t_game *game)
{
    int x, y, dx, dy;
    int *horse_data;
    int horse_color;
    int t;
    int scale = game->horse.scale;

    if (!game->horse.img)
        return;
    horse_data = (int *)mlx_get_data_addr(game->horse.img,
                                          &game->horse.bpp,
                                          &game->horse.line_len,
                                          &game->horse.endian);
    y = 0;
    while (y < game->horse.height)
    {
        x = 0;
        while (x < game->horse.width)
        {
            horse_color = horse_data[y * (game->horse.line_len / 4) + x];
            t = (horse_color >> 24) & 0xFF;
            if (t == 0)
            {
                dy = 0;
                while (dy < scale)
                {
                    dx = 0;
                    while (dx < scale)
                    {
                        int screen_x = game->horse.pos_x + (x * scale) + dx;
                        int screen_y = game->horse.pos_y + (y * scale) + dy;

                        if (screen_x >= 0 && screen_x < game->scr_w &&
                            screen_y >= 0 && screen_y < game->scr_h)
                            pixel_put(&game->img, screen_x, screen_y, horse_color);
                        dx++;
                    }
                    dy++;
                }
            }
            x++;
        }
        y++;
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
        raycast(g);                    // Renders walls to g->img
        mini_map(g);                   // Renders minimap to g->img
        animated_sprite(g);            // Updates horse position
        render_horse_sprite(g);        // Renders horse to g->img
        mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0); // Display everything
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
	free_all_doors(&g->closed_door);
	exit(0);
	return (0);
}
