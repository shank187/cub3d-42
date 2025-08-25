/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-had <abel-had@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:52:44 by abel-had          #+#    #+#             */
/*   Updated: 2025/08/25 10:20:10 by abel-had         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	load_texs(t_game *g)
{
	char	*paths[5];
	int		i;

	g->tex.door = "./textures/door.xpm";
	paths[0] = g->tex.no;
	paths[1] = g->tex.so;
	paths[2] = g->tex.we;
	paths[3] = g->tex.ea;
	paths[4] = g->tex.door;
	i = -1;
	while (++i < 5)
	{
		g->texs[i].img = mlx_xpm_file_to_image(g->mlx, paths[i],
				&g->texs[i].width, &g->texs[i].height);
		if (!g->texs[i].img)
			error_exit(g, "Texture load failed");
		g->texs[i].addr = mlx_get_data_addr(g->texs[i].img,
				&g->texs[i].bpp, &g->texs[i].line_len, &g->texs[i].endian);
	}
}
