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

int	map_h(t_map map)
{
	int	i;

	i = 0;
	while (map.grid[i])
		i++;
	return (i);
}

int	map_w(t_map map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (map.grid[i])
	{
		j = 0;
		while (map.grid[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}
