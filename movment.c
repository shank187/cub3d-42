#include "cub.h"

int	is_wall(t_game *g, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_x >= g->map_w || map_y >= g->map_h)
		return (1);
	return (g->map.grid[map_y][map_x] == '1');
}

int	handle_movement(t_game *g, double move_speed)
{
	double	x;
	double	y;

	x = g->player.x;
	y = g->player.y;
	handle_wasd(g, move_speed, &x, &y);
	if (!is_wall(g, x, y))
	{
		g->player.x = x;
		g->player.y = y;
		return (1);
	}
	return (0);
}

void	rotate_left(t_game *g, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * cos(rot_speed)
		- g->player.dir_y * sin(rot_speed);
	g->player.dir_y = old_dir_x * sin(rot_speed)
		+ g->player.dir_y * cos(rot_speed);
	old_plane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * cos(rot_speed)
		- g->player.plane_y * sin(rot_speed);
	g->player.plane_y = old_plane_x * sin(rot_speed)
		+ g->player.plane_y * cos(rot_speed);
	g->slide_left = 0;
}

void	rotate_right(t_game *g, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * cos(rot_speed)
		+ g->player.dir_y * sin(rot_speed);
	g->player.dir_y = g->player.dir_y * cos(rot_speed)
		- old_dir_x * sin(rot_speed);
	old_plane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * cos(rot_speed)
		+ g->player.plane_y * sin(rot_speed);
	g->player.plane_y = g->player.plane_y * cos(rot_speed)
		- old_plane_x * sin(rot_speed);
	g->slide_right = 0;
}

int	handle_rotation(t_game *g, double rot_speed)
{
	int	moved;

	moved = 0;
	if (g->key_l || g->slide_left)
	{
		rotate_left(g, rot_speed);
		moved = 1;
	}
	if (g->key_r || g->slide_right)
	{
		rotate_right(g, rot_speed);
		moved = 1;
	}
	return (moved);
}
