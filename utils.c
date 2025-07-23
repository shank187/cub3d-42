#include "cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;
	size_t			i;

	i = 0;
	a = (unsigned char *)b;
	while (i < len)
	{
		a[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	error_exit(char *msg)
{
    printf("%s\n", msg);
    exit (1);
}

void clear_screen(t_game *g)
{
    int x;
    int y;

    y = 0;
    while (y < g->scr_h)
    {
        x = 0;
        while (x < g->scr_w)
        {
            if (y < g->scr_h / 2)
                pixel_put(&g->img, x, y, g->tex.ceil);  // Ceiling color
            else
                pixel_put(&g->img, x, y, g->tex.floor); // Floor color
            x++;
        }
        y++;
    }
}
