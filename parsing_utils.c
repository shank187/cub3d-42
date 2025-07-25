/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:04:28 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/25 10:42:38 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void find_angle(t_game *game)
{
	if (game->player.dir == 'N')
		game->player.angle = M_PI_2 * 3;
	if (game->player.dir == 'S')
		game->player.angle = M_PI_2;
	if (game->player.dir == 'E')
		game->player.angle = 0;
	if (game->player.dir == 'W')
		game->player.angle = M_PI;
}

void flood_walls_check(char **arr, int i, int j, t_game *game)
{
	if (!game->map.is_valid)
		return;

	if (i < 0 || j < 0 || arr[i] == NULL || arr[i][j] == '\0' || arr[i][j] == ' ')
	{
		game->map.is_valid = 0;
		return;
	}

	if (arr[i][j] == '1' || arr[i][j] == 'x')
		return;

	if (arr[i][j] != '0')
	{
		game->map.is_valid = 0;
		return;
	}

	arr[i][j] = 'x';
	flood_walls_check(arr, i + 1, j, game);
	flood_walls_check(arr, i - 1, j, game);
	flood_walls_check(arr, i, j + 1, game);
	flood_walls_check(arr, i, j - 1, game);
}

unsigned int	parse_color_rgb(char *line)
{
	int				i;
	unsigned int	color;
	int				n;
	int				bytes;

	i = 1;
	bytes = 3;
	color = 0;
	while (bytes)
	{
		while (line[i] == ' ')
			i++;
		n = ft_atoi(line, &i);
		if (n >= 0)
			 color  = (color << 8) | n;
		else
			return (-1);
		bytes--;
		while (line[i] == ' ' && bytes)
			i++;
		if (line[i] != ',' && bytes)
			return (-1);
		else if (line[i] == ',' && bytes)
			i++;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] != '\n')
		return (-1);
	return (color);
}


char	**parse_map(char *str, t_game *game)
{
	int	i;
	int	j;
	int	found;
	char **map_2d;
	int valid;

	game->player.dir = 0;
	i = 0;
	found = 0;
	while (str[i] == '1' || str[i] == '0' || str[i] == '\n' || str[i] == ' ' \
	|| str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
	{
		if(str[i] == ' ')
			str[i] = '1';
		if (!game->player.dir && (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W'))
			game->player.dir = str[i];
		else if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			return NULL;
		i++;
	}
	if (str[i] || !game->player.dir)
		return (NULL);
	map_2d = ft_split(str, '\n');
	i = 0;
	while(map_2d[i] && !found)
	{
		j = 0;
		while(map_2d[i][j])
		{
			if (map_2d[i][j] == 'N' || map_2d[i][j] == 'S' || map_2d[i][j] == 'E' || map_2d[i][j] == 'W')
			{				
				found = 1;
				break;
			}
			if(!found)
				j++;
		}
		if(!found)
			i++;
	}
	map_2d[i][j] = '0';
	game->player.x = j + 0.5;
	game->player.y = i + 0.5;
	flood_walls_check(map_2d, i, j, game);
	find_angle(game);
	if(!game->map.is_valid)
		return (NULL);
	return (map_2d);
}

// int main(void)
// {
// 	t_game game;

// 	game.map.is_valid = 1;
// 	char **arr = ft_split("1111111\n1000011\n1N01\n100001111\n101100001\n1111111111", '\n');
// 	flood_walls_check(arr, 2, 1, &game); 
// 	printf("%i\n", game.map.is_valid);
// }
