#include "cub3d.h"

int	handle_movement(t_game *g, double move_speed)
{
	int	moved;

	moved = 0;
	if (g->key_w)
	{
		g->p.pos_x += g->p.dir_x * move_speed;
		g->p.pos_y += g->p.dir_y * move_speed;
		moved = 1;
	}
	if (g->key_s)
	{
		g->p.pos_x -= g->p.dir_x * move_speed;
		g->p.pos_y -= g->p.dir_y * move_speed;
		moved = 1;
	}
	if (g->key_a)
	{
		g->p.pos_x += g->p.dir_y * move_speed;
		g->p.pos_y -= g->p.dir_x * move_speed;
		moved = 1;
	}
	if (g->key_d)
	{
		g->p.pos_x -= g->p.dir_y * move_speed;
		g->p.pos_y += g->p.dir_x * move_speed;
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
		old_dir_x = g->p.dir_x;
		g->p.dir_x = g->p.dir_x * cos(rot_speed) - g->p.dir_y * sin(rot_speed);
		g->p.dir_y = old_dir_x * sin(rot_speed) + g->p.dir_y * cos(rot_speed);
		old_plane_x = g->p.plane_x;
		g->p.plane_x = g->p.plane_x * cos(rot_speed) - g->p.plane_y * sin(rot_speed);
		g->p.plane_y = old_plane_x * sin(rot_speed) + g->p.plane_y * cos(rot_speed);
		moved = 1;
	}
	if (g->key_r)
	{
		old_dir_x = g->p.dir_x;
		g->p.dir_x = g->p.dir_x * cos(-rot_speed) - g->p.dir_y * sin(-rot_speed);
		g->p.dir_y = old_dir_x * sin(-rot_speed) + g->p.dir_y * cos(-rot_speed);
		old_plane_x = g->p.plane_x;
		g->p.plane_x = g->p.plane_x * cos(-rot_speed) - g->p.plane_y * sin(-rot_speed);
		g->p.plane_y = old_plane_x * sin(-rot_speed) + g->p.plane_y * cos(-rot_speed);
		moved = 1;
	}
	return (moved);
}
