/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:43:04 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/26 10:55:02 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_my_struct(t_game *game)
{
	game->ceiling_color = UINT32_MAX;
	game->floor_color = UINT32_MAX;
	game->player.angle = -1;
	game->player.dir = 0;
	game->player.x = -1;
	game->player.y = -1;
	game->map.grid = NULL;
	game->map.is_valid = 1;
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
}

void	clean_parsing_stuff(t_game *game)
{
	int	i;

	free(game->textures.ea);
	free(game->textures.so);
	free(game->textures.no);
	free(game->textures.we);
	i = -1;
	while (game->map.grid && game->map.grid[++i])
	{
		free(game->map.grid[i]);
	}
	free(game->map.grid);
}

void	clean_data(t_game *game)
{
	ft_replace_chr(game->textures.no, NULL, '\n', 0);
	ft_replace_chr(game->textures.so, NULL, '\n', 0);
	ft_replace_chr(game->textures.we, NULL, '\n', 0);
	ft_replace_chr(game->textures.ea, NULL, '\n', 0);
	ft_replace_chr(game->textures.no, NULL, ' ', 0);
	ft_replace_chr(game->textures.so, NULL, ' ', 0);
	ft_replace_chr(game->textures.we, NULL, ' ', 0);
	ft_replace_chr(game->textures.ea, NULL, ' ', 0);
	ft_replace_chr(NULL, game->map.grid, 'x', '0');
}

int	store_map_infos(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) && !game->textures.no && \
			ft_strchr(line, '.'))
		game->textures.no = ft_strdup(ft_strchr(line, '.'), game);
	else if (!ft_strncmp(line, "SO ", 3) && !game->textures.so && \
			ft_strchr(line, '.'))
		game->textures.so = ft_strdup(ft_strchr(line, '.'), game);
	else if (!ft_strncmp(line, "WE ", 3) && !game->textures.we && \
			ft_strchr(line, '.'))
		game->textures.we = ft_strdup(ft_strchr(line, '.'), game);
	else if (!ft_strncmp(line, "EA ", 3) && !game->textures.ea && \
			ft_strchr(line, '.'))
		game->textures.ea = ft_strdup(ft_strchr(line, '.'), game);
	else if (!ft_strncmp(line, "F ", 2) && game->floor_color == UINT32_MAX)
		game->floor_color = parse_color_rgb(line);
	else if (!ft_strncmp(line, "C ", 2) && game->ceiling_color == UINT32_MAX)
		game->ceiling_color = parse_color_rgb(line);
	else
		return (0);
	return (1);
}

int	is_valid_extension(char *filename, char *identifier)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	i = ft_strlen(identifier);
	j = ft_strlen(filename);
	k = 0;
	while (identifier[k] && filename[j - i] && \
			identifier[k++] == filename[j++ - i])
		;
	return (!filename[j - i]);
}
