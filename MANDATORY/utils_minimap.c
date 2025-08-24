/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-had <abel-had@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:52:37 by abel-had          #+#    #+#             */
/*   Updated: 2025/08/24 10:52:38 by abel-had         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_minimap(t_minimap *v, t_game *game)
{
	v->minimap_w = SCREEN_WIDTH / 8;
	v->minimap_h = SCREEN_HEIGHT / 8;
	v->start_x = SCREEN_WIDTH / 20;
	v->start_y = SCREEN_HEIGHT / 20;
	v->minigrid_w = v->minimap_w / game->map_w;
	v->minigrid_h = v->minimap_h / game->map_h;
	if (v->minigrid_w < 1)
		v->minigrid_w = 1;
	if (v->minigrid_h < 1)
		v->minigrid_h = 1;
	v->player_screen_x = v->start_x + (int)(game->player.x * v->minigrid_w);
	v->player_screen_y = v->start_y + (int)(game->player.y * v->minigrid_h);
	v->dot_size = 2;
}

int	get_tile_color(t_game *game, int map_y, int map_x)
{
	if (game->map.grid[map_y][map_x] == '1')
		return (WALL_COLOR);
	else if (game->map.grid[map_y][map_x] == '2')
		return (DOOR_COLOR);
	else
		return (FLOOR_COLOR);
}

void	draw_minimap_tile(t_game *game, t_minimap *v, int map_x, int map_y)
{
	int	screen_x;
	int	screen_y;
	int	color;
	int	y;
	int	x;

	screen_x = v->start_x + (map_x * v->minigrid_w);
	screen_y = v->start_y + (map_y * v->minigrid_h);
	color = get_tile_color(game, map_y, map_x);
	y = -1;
	while (++y < v->minigrid_h)
	{
		x = -1;
		while (++x < v->minigrid_w)
			pixel_put(&game->img, screen_x + x, screen_y + y, color);
	}
}

void	draw_minimap_grid(t_game *game, t_minimap *v)
{
	int	map_x;

	v->map_y = 0;
	while (v->map_y < game->map_h)
	{
		map_x = 0;
		while (map_x < game->map_w)
		{
			draw_minimap_tile(game, v, map_x, v->map_y);
			map_x++;
		}
		v->map_y++;
	}
}

void	draw_player_dot(t_game *game, t_minimap *v)
{
	v->py = -2;
	while (v->py <= v->dot_size)
	{
		v->px = -2;
		while (v->px <= v->dot_size)
		{
			pixel_put(&game->img, v->player_screen_x + v->px,
				v->player_screen_y + v->py, PLAYER_COLOR);
			v->px++;
		}
		v->py++;
	}
}
