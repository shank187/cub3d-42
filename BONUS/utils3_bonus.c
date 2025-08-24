/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-had <abel-had@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:52:23 by abel-had          #+#    #+#             */
/*   Updated: 2025/08/24 10:52:24 by abel-had         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
