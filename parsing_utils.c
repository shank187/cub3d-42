/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:04:28 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/23 11:18:28 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

// int main(void)
// {
// 	t_game game;

// 	game.map.is_valid = 1;
// 	char **arr = ft_split("1111111\n1000011\n1N01\n100001111\n101100001\n1111111111", '\n');
// 	flood_walls_check(arr, 2, 1, &game); 
// 	printf("%i\n", game.map.is_valid);
// }
