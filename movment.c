#include "cub.h"

int	is_wall(t_game *g, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	return (g->map.grid[map_y][map_x] == '1');
}

int	handle_movement(t_game *g, double move_speed)
{
	double x;
	double y;

	x = g->player.x;
	y = g->player.y;
	if (g->key_w)
	{
		x += g->player.dir_x * move_speed;
		y += g->player.dir_y * move_speed;
	}
	if (g->key_s)
	{
		x -= g->player.dir_x * move_speed;
		y -= g->player.dir_y * move_speed;
	}
	if (g->key_d)
	{
		x += g->player.dir_y * move_speed;
		y -= g->player.dir_x * move_speed;
	}
	if (g->key_a)
	{
		x -= g->player.dir_y * move_speed;
		y += g->player.dir_x * move_speed;
	}
	// if (x == g->player.x && y == g->player.y)
	// 	return (0);
	if (!is_wall(g, x, y))
	{
		g->player.x = x;
		g->player.y = y;
		return (1);
	}
	else
		return (0);
}

int	handle_rotation(t_game *g, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;
	int		moved;

	moved = 0;
	if (g->key_l || g->slide_left)
	{
		old_dir_x = g->player.dir_x;
		g->player.dir_x = g->player.dir_x * cos(rot_speed) - g->player.dir_y * sin(rot_speed);
		g->player.dir_y = old_dir_x * sin(rot_speed) + g->player.dir_y * cos(rot_speed);
		old_plane_x = g->player.plane_x;
		g->player.plane_x = g->player.plane_x * cos(rot_speed) - g->player.plane_y * sin(rot_speed);
		g->player.plane_y = old_plane_x * sin(rot_speed) + g->player.plane_y * cos(rot_speed);
		moved = 1;
		g->slide_left = 0;
	}
	if (g->key_r || g->slide_right)
	{
		old_dir_x = g->player.dir_x;
		g->player.dir_x = g->player.dir_x * cos(-rot_speed) - g->player.dir_y * sin(-rot_speed);
		g->player.dir_y = old_dir_x * sin(-rot_speed) + g->player.dir_y * cos(-rot_speed);
		old_plane_x = g->player.plane_x;
		g->player.plane_x = g->player.plane_x * cos(-rot_speed) - g->player.plane_y * sin(-rot_speed);
		g->player.plane_y = old_plane_x * sin(-rot_speed) + g->player.plane_y * cos(-rot_speed);
		moved = 1;
		g->slide_right = 0;
	}
	return (moved);
}
