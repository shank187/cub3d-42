#include "cub3d.h"

void	load_texs(t_game *g)
{
	char	*paths[4];
	int		i;

	paths[0] = g->tex.no;
	paths[1] = g->tex.so;
	paths[2] = g->tex.we;
	paths[3] = g->tex.ea;
	i = -1;
	while (++i < 4)
	{
		g->texs[i].img = mlx_xpm_file_to_image(g->mlx, paths[i],
				&g->texs[i].width, &g->texs[i].height);
		if (!g->texs[i].img)
			error_exit("Texture load failed");
		g->texs[i].addr = mlx_get_data_addr(g->texs[i].img,
				&g->texs[i].bpp, &g->texs[i].line_len, &g->texs[i].endian);
	}
}