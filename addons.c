/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:59:24 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/20 10:23:46 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    render_horse_sprite(t_game *game)
{
	t_horse	*h;
	int scale;

	scale = game->horse.scale;
	h = &game->horse;
	if (!game->horse.img)
		return ;
	h->horse_data = (int *)mlx_get_data_addr(game->horse.img, \
										&game->horse.bpp, \
										&game->horse.line_len, \
										&game->horse.endian);
	h->y = 0;
	while (h->y < game->horse.height)
	{
		h->x = 0;
		while (h->x < game->horse.width)
		{
			h->horse_color = h->horse_data[h->y * \
			(game->horse.line_len / 4) + h->x];
			h->t = (h->horse_color >> 24) & 0xFF;
			if (h->t == 0)
			{
				h->dy = 0;
				while (h->dy < scale)
				{
					h->dx = 0;
					while (h->dx < scale)
					{
						h->screen_x = game->horse.pos_x + (h->x * scale) + h->dx;
						h->screen_y = game->horse.pos_y + (h->y * scale) + h->dy;
						if (h->screen_x >= 0 && h->screen_x < game->scr_w && \
							h->screen_y >= 0 && h->screen_y < game->scr_h)
							pixel_put(&game->img, h->screen_x, \
							h->screen_y, h->horse_color);
						h->dx++;
					}
					h->dy++;
				}
			}
			h->x++;
		}
		h->y++;
	}
}

void	animated_sprite(t_game *game)
{
	static int	frame;
	static int	dir;
	int			offset;

	if (! dir)
		dir = 1;
	if (frame >= 50)
		dir = -1;
	if (frame <= 0)
		dir = 1;
	frame += dir;
	offset = frame / 2;
	game->horse.pos_y = game->horse.base_pos_y + offset;
}

int	mouse_move(int x, int y, void *param)
{
	static int 	old_x;
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