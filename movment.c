#include "cub.h"

int	handle_movement(t_game *g, double move_speed)
{
	int	moved;

	moved = 0;
	if (g->key_w)
	{
		g->player.x += g->player.dir_x * move_speed;
		g->player.y += g->player.dir_y * move_speed;
		moved = 1;
	}
	if (g->key_s)
	{
		g->player.x -= g->player.dir_x * move_speed;
		g->player.y -= g->player.dir_y * move_speed;
		moved = 1;
	}
	if (g->key_a)
	{
		g->player.x += g->player.dir_y * move_speed;
		g->player.y -= g->player.dir_x * move_speed;
		moved = 1;
	}
	if (g->key_d)
	{
		g->player.x -= g->player.dir_y * move_speed;
		g->player.y += g->player.dir_x * move_speed;
		moved = 1;
	}
	return (moved);
}

int	handle_rotation(t_game *g, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;
	int		moved;

	moved = 0;
	if (g->key_l)
	{
		old_dir_x = g->player.dir_x;
		g->player.dir_x = g->player.dir_x * cos(rot_speed) - g->player.dir_y * sin(rot_speed);
		g->player.dir_y = old_dir_x * sin(rot_speed) + g->player.dir_y * cos(rot_speed);
		old_plane_x = g->player.plane_x;
		g->player.plane_x = g->player.plane_x * cos(rot_speed) - g->player.plane_y * sin(rot_speed);
		g->player.plane_y = old_plane_x * sin(rot_speed) + g->player.plane_y * cos(rot_speed);
		moved = 1;
	}
	if (g->key_r)
	{
		old_dir_x = g->player.dir_x;
		g->player.dir_x = g->player.dir_x * cos(-rot_speed) - g->player.dir_y * sin(-rot_speed);
		g->player.dir_y = old_dir_x * sin(-rot_speed) + g->player.dir_y * cos(-rot_speed);
		old_plane_x = g->player.plane_x;
		g->player.plane_x = g->player.plane_x * cos(-rot_speed) - g->player.plane_y * sin(-rot_speed);
		g->player.plane_y = old_plane_x * sin(-rot_speed) + g->player.plane_y * cos(-rot_speed);
		moved = 1;
	}
	return (moved);
}
