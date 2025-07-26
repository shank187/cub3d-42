/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:22:33 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/26 10:23:15 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == '\n' || c == ' ' || \
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	set_player_direction(char c, t_game *game)
{
	if (!game->player.dir && (c == 'N' || c == 'S' || c == 'E' || c == 'W'))
	{
		game->player.dir = c;
		return (1);
	}
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

static int	validate_and_parse_chars(char *str, t_game *game)
{
	int	i;

	i = 0;
	game->player.dir = 0;
	while (str[i] && is_valid_map_char(str[i]))
	{
		if (str[i] == ' ')
			str[i] = '1';
		if (!set_player_direction(str[i], game))
			return (0);
		i++;
	}
	if (str[i] || !game->player.dir)
		return (0);
	return (1);
}

static void	set_player_position(char **map, t_game *game)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	found = 0;
	while (map[i] && !found)
	{
		j = 0;
		while (map[i][j] && !found)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				map[i][j] = '0';
				found = 1;
			}
			j++;
		}
		i++;
	}
}

char	**parse_map(char *str, t_game *game)
{
	char	**map;

	if (!validate_and_parse_chars(str, game))
		return (NULL);
	map = ft_split(str, '\n', game);
	if (!map)
		return (NULL);
	set_player_position(map, game);
	flood_walls_check(map, (int)game->player.y, (int)game->player.x, game);
	find_angle(game);
	if (!game->map.is_valid)
		return (NULL);
	return (map);
}
