#include "cub.h"

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