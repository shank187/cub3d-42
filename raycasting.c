#include "cub.h"

int	map_g(t_ray *r, t_game *g)
{
	return (r->map_y < 0 || r->map_y >= g->map_h
		|| r->map_x < 0 || r->map_x >= g->map_w);
}

int	tex_nb(t_ray *r)
{
	if (r->door)
		return (4);
	else if (r->side == 0)
	{
		if (r->step_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (r->step_y > 0)
			return (1);
		else
			return (0);
	}
}

void	draw_line_part1(t_game *g, t_ray *r, double *step, double *tex_pos)
{
	if (r->side == 0)
		r->wall_x = g->player.y + r->wall_dist * r->ray_dir_y;
	else
		r->wall_x = g->player.x + r->wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)TEX_WIDTH);
	*step = (double)TEX_HEIGHT / r->line_h;
	*tex_pos = (r->draw_s - g->scr_h / 2 + r->line_h / 2) * (*step);
}

// floor(x) instead of (int)x solve negatve nbrs !!!
void	draw_line(t_game *g, t_ray *r, int x)
{
	int		y;
	int		color;
	int		tex_num;
	double	step;
	double	tex_pos;

	tex_num = tex_nb(r);
	draw_line_part1(g, r, &step, &tex_pos);
	y = -1;
	while (++y < r->draw_s)
		pixel_put(&g->img, x, y, g->ceiling_color);
	y = r->draw_s;
	while (y < r->draw_e)
	{
		r->tex_y = (int)tex_pos % TEX_HEIGHT;
		tex_pos += step;
		color = *(int *)(g->texs[tex_num].addr + (r->tex_y
					* g->texs[tex_num].line_len + r->tex_x
					* (g->texs[tex_num].bpp / 8)));
		pixel_put(&g->img, x, y, color);
		y++;
	}
	while (y++ < g->scr_h)
		pixel_put(&g->img, x, y, g->floor_color);
}

void	raycast(t_game *g)
{
	int		x;
	t_ray	r;

	x = -1;
	while (++x < g->scr_w)
	{
		init_ray(g, &r, x);
		calc_step(g, &r);
		dda(g, &r);
		calc_wall_dist(g, &r);
		calc_wall_h(g, &r);
		draw_line(g, &r, x);
	}
}
