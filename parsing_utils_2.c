/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:01:26 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/26 10:55:43 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_map_start(t_game *game)
{
	return (game->textures.ea && game->textures.no
		&& game->textures.so && game->textures.we
		&& game->ceiling_color != UINT32_MAX
		&& game->floor_color != UINT32_MAX);
}

static int	handle_line_before_map(char *line, t_game *game)
{
	if (!store_map_infos(game, line))
	{
		ft_putstr_fd("Error\nINCOMPLET | INCORRECT INFOS.\n", 2);
		free(line);
		return (0);
	}
	return (1);
}

static int	append_map_line(char **map, char *line, t_game *game)
{
	char	*tmp;

	tmp = *map;
	*map = ft_strjoin(*map, line, game);
	free(tmp);
	if (!*map)
		return (0);
	return (1);
}

static int	process_line(char *line, t_game *game,
	int *on_map, char **map)
{
	if (!*on_map && !ft_strncmp("\n", line, 13))
		return (free(line), 2);
	if (ft_strncmp("\n", line, 13) && !*on_map && is_map_start(game))
		*on_map = 1;
	if (!*on_map && ft_strncmp("\n", line, 13))
		return (handle_line_before_map(line, game));
	if (*on_map && ft_strncmp("\n", line, 13))
	{
		if (!append_map_line(map, line, game))
		{
			ft_putstr_fd("Error\nMemory error.\n", 2);
			free(line);
			return (0);
		}
		return (1);
	}
	ft_putstr_fd("Error\nINCOMPLET | INCORRECT INFOS.\n", 2);
	free(line);
	return (0);
}

void	*extract_and_store_data(int fd, t_game *game)
{
	char	*line;
	int		on_map;
	char	*map;
	int		result;

	on_map = 0;
	map = NULL;
	line = get_next_line(fd, game);
	while (line)
	{
		result = process_line(line, game, &on_map, &map);
		if (result == 0)
			return (NULL);
		else if (result != 2)
			free(line);
		if (result != 0 && result != 2)
			line = get_next_line(fd, game);
		if (result == 2)
			line = get_next_line(fd, game);
	}
	game->map.grid = parse_map(map, game);
	if (!game->map.grid)
		return (ft_putstr_fd("Error\nINVALID MAP!!.\n", 2), NULL);
	return (game);
}
