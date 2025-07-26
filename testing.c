#include "cub.h"


void	extract_rgb_from_uint32(unsigned int color)
{
	int				i;
	int				holder;
	unsigned char	c;

	i = 16;
	while (i >= 0)
	{
		holder = color;
		holder = holder >> i;
		c = (char) holder;
		printf("|%i|", c);
		i -= 8;
	}
	printf("\n");
}

void show_data_strored(t_game *game)
{

	printf("player initial pos x = %f | y = %f\nplayer initial dir %c\nplayer angle %f\n", game->player.x, game->player.y, game->player.dir, game->player.angle);
	printf("\nnorth texture |%s|\n", game->textures.no);
	printf("south texture |%s|\n", game->textures.so);
	printf("west texture |%s|\n", game->textures.we);
	printf("east texture |%s|\n\n", game->textures.ea);
	int  i = -1;
	while(game->map.grid[++i])
	{
		printf("|%s|\n", game->map.grid[i]);
	}
	printf("\nceiling color as unsigned int : (%u) & bytes => ", game->ceiling_color);
	extract_rgb_from_uint32(game->ceiling_color);
	printf("floor color as unsigned int : (%u) & bytes => ", game->floor_color);
	extract_rgb_from_uint32(game->floor_color);
}