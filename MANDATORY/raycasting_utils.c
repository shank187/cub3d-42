/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-had <abel-had@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:53:28 by abel-had          #+#    #+#             */
/*   Updated: 2025/08/24 10:53:29 by abel-had         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_ray(t_game *g, t_ray *r, int x)
{
	r->cam_x = 2 * x / (double)g->scr_w - 1;
	r->map_x = (int)g->player.x;
	r->map_y = (int)g->player.y;
	r->ray_dir_x = g->player.dir_x + g->player.plane_x * r->cam_x;
	r->ray_dir_y = g->player.dir_y + g->player.plane_y * r->cam_x;
	if (r->ray_dir_x == 0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1 / r->ray_dir_y);
}

void	calc_step(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (g->player.x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - g->player.x) * r->delta_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (g->player.y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - g->player.y) * r->delta_y;
	}
}

void	dda(t_game *g, t_ray *r)
{
	r->door = false;
	while (1)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (map_g(r, g))
			break ;
		else if (g->map.grid[r->map_y][r->map_x] == '1')
			break ;
		else if (g->map.grid[r->map_y][r->map_x] == '2')
		{
			r->door = true;
			break ;
		}
	}
}

void	calc_wall_dist(t_game *g, t_ray *r)
{
	(void)g;
	if (r->side == 0)
		r->wall_dist = (r->map_x - g->player.x
				+ (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		r->wall_dist = (r->map_y - g->player.y
				+ (1 - r->step_y) / 2) / r->ray_dir_y;
	if (r->wall_dist < 0.001)
		r->wall_dist = 0.009;
}

void	calc_wall_h(t_game *g, t_ray *r)
{
	r->line_h = (int)(g->scr_h / r->wall_dist);
	r->draw_s = -r->line_h / 2 + g->scr_h / 2;
	if (r->draw_s < 0)
		r->draw_s = 0;
	r->draw_e = r->line_h / 2 + g->scr_h / 2;
	if (r->draw_e >= g->scr_h)
		r->draw_e = g->scr_h - 1;
}
