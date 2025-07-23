/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:04:28 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/23 10:09:42 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


int is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void flood_fill(char **arr, int i, int j, t_game *game)
{
	if (!game->map.is_valid)
		return;

	if (arr[i] == NULL || arr[i][j] == '\0' || arr[i][j] == ' ')
	{
		game->map.is_valid = 0;
		return;
	}

	if (arr[i][j] == '1' || arr[i][j] == 'x')
		return;

	if (!is_walkable(arr[i][j]))
	{
		game->map.is_valid = 0;
		return;
	}

	arr[i][j] = 'x';

	flood_fill(arr, i + 1, j, game);
	flood_fill(arr, i - 1, j, game);
	flood_fill(arr, i, j + 1, game);
	flood_fill(arr, i, j - 1, game);
}




int main(void)
{
	t_game game;

	game.map.is_valid = 1;
	char **arr = ft_split("010110\n100N01\n100001\n111111\n", '\n');
	flood_fill(arr, 1, 3, &game); 
	printf("%i\n", game.map.is_valid);
}
