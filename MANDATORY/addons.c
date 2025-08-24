/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-had <abel-had@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:59:24 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/24 13:26:37 by abel-had         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	mouse_move(int x, int y, void *param)
{
	static int	old_x;
	t_game		*game;

	game = (t_game *) param;
	if (y < 0 || y >= game->scr_h)
		return (0);
	if (x >= 0 && x <= game->scr_w && x < old_x)
	{
		game->slide_left = 1;
		old_x = x;
	}
	if (x >= 0 && x <= game->scr_w && x > old_x)
	{
		game->slide_right = 1;
		old_x = x;
	}
	return (0);
}
