/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:04:28 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/07 10:46:13 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_strjoin_char(char **str, char c, size_t size, t_game *game)
{
	char	*to_add;
	char	*tmp;

	to_add = malloc(size + 1);
	if (!to_add)
		return (clean_parsing_stuff(game), exit(1));
	ft_memset(to_add, c, size);
	to_add[size] = 0;
	tmp = *str;
	*str = ft_strjoin(*str, to_add, game);
	free(tmp);
	free(to_add);
}

void	ft_fix_sizes(char **arr, char c, t_game *game)
{
	size_t	max;
	size_t	i;

	i = 0;
	max = ft_strlen(arr[i]);
	while (arr[++i])
		if (ft_strlen(arr[i]) > max)
			max = ft_strlen(arr[i]);
	i = -1;
	while (arr[++i])
	{
		if (ft_strlen(arr[i]) < max)
			ft_strjoin_char(&arr[i], c, max - ft_strlen(arr[i]), game);
	}
}


void	flood_walls_check(char **arr, int i, int j, t_game *game)
{
	if (!game->map.is_valid)
		return ;
	if (i < 0 || j < 0 || arr[i] == NULL || \
		arr[i][j] == '\0')
	{
		return ;
	}
	if (arr[i][j] == '1' || arr[i][j] == 'x')
		return ;
	if (arr[i][j] != 'v')
	{
		game->map.is_valid = 0;
		return ;
	}
	arr[i][j] = 'x';
	flood_walls_check(arr, i + 1, j + 1 , game);
	flood_walls_check(arr, i - 1, j + 1 , game);
	flood_walls_check(arr, i + 1, j, game);
	flood_walls_check(arr, i - 1, j, game);
	flood_walls_check(arr, i - 1, j - 1, game);
	flood_walls_check(arr, i + 1, j - 1, game);
	flood_walls_check(arr, i, j + 1, game);
	flood_walls_check(arr, i, j - 1, game);
}

int	surrended_walls_check(char **arr)
{
	int	j;
	int	i;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if ((i == 0 || j == 0) && arr[i][j] != '1')
				return (0);
			else if ((!arr[i][j + 1] || !arr[i + 1]) && arr[i][j] != '1')
				return (0);
		}
	}
	return (1);
}

unsigned int	process_rgb_seq(char *line, int *i, \
							unsigned int *color, int *bytes)
{
	int	n;

	while (line[(*i)] == ' ')
		(*i)++;
	n = ft_atoi(line, i);
	if (n >= 0)
		(*color) = ((*color) << 8) | n;
	else
		return (0);
	while (line[(*i)] == ' ' && (*bytes))
		(*i)++;
	if (line[(*i)] != ',' && (*bytes))
		return (0);
	else if (line[(*i)] == ',' && (*bytes))
		(*i)++;
	return (1);
}

unsigned int	parse_color_rgb(char *line)
{
	int				i;
	unsigned int	color;
	int				bytes;

	i = 1;
	bytes = 3;
	color = 0;
	while (bytes)
	{
		bytes--;
		if (!process_rgb_seq(line, &i, &color, &bytes))
			return (-1);
	}
	while (line[i] == ' ')
		i++;
	if (line[i] != '\n')
		return (-1);
	return (color);
}
