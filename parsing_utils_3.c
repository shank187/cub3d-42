/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:22:33 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/19 15:09:21 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

char	**cover_all_sides(char **map, t_game *game)
{
	int		i;
	char	*fill_start;
	char	*fill_end;
	char	**new_map;
	char	*tmp;

	i = -1;
	while (map[++i])
		;
	fill_start = malloc(ft_strlen(map[0]) + (2) + 1);
	ft_memset(fill_start, 'v', ft_strlen(map[0]) + (2));
	fill_start[ft_strlen(map[0]) + (2)] = 0;
	fill_end = malloc(ft_strlen(map[0]) + (2) + 1);
	ft_memset(fill_end, 'v', ft_strlen(map[0]) + (2));
	fill_end[ft_strlen(map[0]) + (2)] = 0;
	new_map = malloc (sizeof(char *) * (i + 3));
	new_map[0] = fill_start;
	new_map[i + 1] = fill_end;
	new_map[i + 2] = NULL;
	i = -1;
	while (map[++i])
	{
		new_map[i + 1] = ft_strjoin(map[i], "v", game);
		tmp = new_map[i + 1];
		new_map[i + 1] = ft_strjoin("v", tmp, game);
		free(tmp);
	}
	i = -1;
	while (new_map[++i])
		printf("%s\n", new_map[i]);
	return (new_map);
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
	// printf("test\n");
	map = ft_split(str, '\n', game);
	if (!map)
		return (free_2d_arr(initial_map), NULL);
	set_player_position(map, game);
	initial_map[(int)game->player.y][(int)game->player.x] = '0';
	free_2d_arr(map);
	ft_replace_chr(NULL, initial_map, ' ', '0');
	if (!validate_doors(initial_map))
		return (free_2d_arr(initial_map), NULL);
	ft_fix_sizes(initial_map, 'v', game);
	map = cover_all_sides(initial_map, game);
	free_2d_arr(initial_map);
	flood_walls_check(map, 0, 0, game);
	// printf("\n\n");
	// int i = 0;
	// while(map[i])
	// 	printf("%s\n", map[i++]);
	// printf("\n\n");
	if (!game->map.is_valid)
		return (free_2d_arr(map), NULL);
	return (map);
}
