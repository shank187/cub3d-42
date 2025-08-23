#include "cub.h"

void	handle_wasd(t_game *g, double move_speed, double *x, double *y)
{
	if (g->key_w)
	{
		*x += g->player.dir_x * move_speed;
		*y += g->player.dir_y * move_speed;
	}
	if (g->key_s)
	{
		*x -= g->player.dir_x * move_speed;
		*y -= g->player.dir_y * move_speed;
	}
	if (g->key_d)
	{
		*x += g->player.dir_y * move_speed;
		*y -= g->player.dir_x * move_speed;
	}
	if (g->key_a)
	{
		*x -= g->player.dir_y * move_speed;
		*y += g->player.dir_x * move_speed;
	}
}
