/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:02:06 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/24 10:26:07 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	validate_doors(char **arr)
{
	int	i;
	int	j;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (arr[i][j] == '2')
			{
				if ((j == 0 && (i == 0 || !arr[i + 1])) || \
					(!arr[i][j + 1] && (i == 0 || !arr[i + 1])))
					return (0);
				else if ((i && arr[i - 1][j] == '1' && \
					arr[i + 1] && arr[i + 1][j] == '1'))
					;
				else if (j && arr[i][j - 1] == '1' && arr[i][j + 1] == '1')
					;
				else
					return (0);
			}
		}
	}
	return (1);
}

void	filling_sides(char **new_map, char **map, t_game *game)
{
	int		i;
	char	*tmp;

	i = -1;
	while (map[++i])
	{
		new_map[i + 1] = ft_strjoin(map[i], "v", game);
		tmp = new_map[i + 1];
		new_map[i + 1] = ft_strjoin("v", tmp, game);
		free(tmp);
	}
}

char	**padding_char_2d(char **map, t_game *game)
{
	int		i;
	char	*fill_start;
	char	*fill_end;
	char	**new_map;

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
	filling_sides(new_map, map, game);
	return (new_map);
}
