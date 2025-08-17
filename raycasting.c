#include "cub.h"

void init_ray(t_game *g, t_ray *r, int x)
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

void calc_step(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (g->player.x - r->map_x) * r->delta_x; // r->map x , y : which box of the map we're in
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

void dda(t_game *g, t_ray *r)
{
	r->door = false;
	while (1)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0; // east, west
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1; // south , north
		}
		if (r->map_y < 0 || r->map_y >= g->map_h || r->map_x < 0 || r->map_x >= g->map_w)
			break;
		else if (g->map.grid[r->map_y][r->map_x] == '1')
			break;
		else if (g->map.grid[r->map_y][r->map_x] == '2')
		{
			r->door = true;
			break;
		}
	}
}

void calc_wall_dist(t_game *g, t_ray *r)
{
	(void)g;
	if (r->side == 0)                            // if we hit the wall from the left or the right
		r->wall_dist = r->side_x - r->delta_x; //r->wall_dist = (r->map_x - g->player.x + (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		r->wall_dist = r->side_y - r->delta_y; //r->wall_dist = (r->map_y - g->player.y + (1 - r->step_y) / 2) / r->ray_dir_y;
	if (r->wall_dist < 0.001)
        r->wall_dist = 0.009;
	// f}\n",r->wall_dist);
}

void calc_wall_h(t_game *g, t_ray *r)
{
	r->line_h = (int)(g->scr_h / r->wall_dist);
	r->draw_s = -r->line_h / 2 + g->scr_h / 2;
	if (r->draw_s < 0)
		r->draw_s = 0;
	r->draw_e = r->line_h / 2 + g->scr_h / 2;
	if (r->draw_e >= g->scr_h)
		r->draw_e = g->scr_h - 1;
}

// floor(x) instead of (int)x solve negatve nbrs !!! 
void draw_line(t_game *g, t_ray *r, int x)
{
	int y;
	int color;
	int tex_num;
	double step;
	double tex_pos;

	if (r->door)
		tex_num = 4;
	else if (r->side == 0)
	{
		if (r->step_x > 0)
			tex_num = 2; // EAST
		else
			tex_num = 3; // WEST
	}
	else
	{
		if (r->step_y > 0)
			tex_num = 1; // SOUTH
		else
			tex_num = 0; // NORTH
	}
	if (r->side == 0)
		r->wall_x = g->player.y + r->wall_dist * r->ray_dir_y;
	else														// wall_x is the fractional position along the wall (0.0 = left edge, 1.0 = right edge)
		r->wall_x = g->player.x + r->wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);                           // Get fractional part (0.0 to 1.0)
	r->tex_x = (int)(r->wall_x * (double)TEX_WIDTH);         //tex_x converts this to a pixel coordinate in the texture (0 to 63 if TEX_WIDTH = 64)
	if ((r->side == 0 && r->ray_dir_x > 0) || (r->side == 1 && r->ray_dir_y < 0))
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
		
	step = 1.0 * TEX_HEIGHT / r->line_h; 	//For step < 1.0 (close walls):
											// The texture is oversampled (some pixels are reused).
											// Can cause blockiness, but your line_h clamping minimizes this.

											//For step >= 1.0 (far walls):
											//The texture is undersampled (some pixels are skipped).
											//On low-resolution walls, this isn’t visibly noticeable.
	tex_pos = (r->draw_s - g->scr_h / 2 + r->line_h / 2) * step; // calculate the starting vertical position in the texture for drawing a wall slice
	y = -1;
	while (++y < r->draw_s)
		pixel_put(&g->img, x, y, g->ceiling_color);
	y = r->draw_s;
	// printf("[%d]----[%d]\n", r->draw_s , r->draw_e);
	while (y < r->draw_e)
	{
		r->tex_y = (int)tex_pos % TEX_HEIGHT;
		tex_pos += step;
		color = *(int *)(g->texs[tex_num].addr + (r->tex_y * g->texs[tex_num].line_len + r->tex_x * (g->texs[tex_num].bpp / 8)));
		//				texture[texNum]           [  texY   *  texHeight                      +  texX]
		
		// printf("[%d]\n", color);
		pixel_put(&g->img, x, y, color);
		y++;
	}
	while (y++ < g->scr_h)
		pixel_put(&g->img, x, y, g->floor_color);
	
}

void raycast(t_game *g)
{
	int x;
	t_ray r;

	x = -1;
	// printf("_+++++\n");
	while (++x < g->scr_w)
	{
		init_ray(g, &r, x);
		calc_step(g, &r); // how much steps x, y to hit the wall
		dda(g, &r);
		calc_wall_dist(g, &r);
		calc_wall_h(g, &r);
		draw_line(g, &r, x);
		// printf("++++\n");
	}
}