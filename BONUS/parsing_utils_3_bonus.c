/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:22:33 by aelbour           #+#    #+#             */
/*   Updated: 2025/09/19 15:58:09 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == '\n' || c == ' ' || \
			c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '2');
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
		if (str[i] == '2')
			str[i] = '0';
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
	char	**initial_map;
	char	**map;

	initial_map = ft_split(str, '\n', game);
	if (!initial_map)
		return (NULL);
	if (!validate_and_parse_chars(str, game))
		return (free_2d_arr(initial_map), NULL);
	map = ft_split(str, '\n', game);
	if (!map)
		return (free_2d_arr(initial_map), NULL);
	free_2d_arr(map);
	ft_replace_chr(NULL, initial_map, ' ', '1');
	if (!validate_doors(initial_map))
		return (free_2d_arr(initial_map), NULL);
	ft_fix_sizes(initial_map, 'v', game);
	map = padding_char_2d(initial_map, game);
	set_player_position(map, game);
	free_2d_arr(initial_map);
	if (!iter_flood_check(map, 0, 0, game))
		return (free_2d_arr(map), NULL);
	return (map);
}
